/****************************************************************************
 *
 *   (c) 2009-2016 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#include "PositionManager.h"
#include "QGCApplication.h"
#include "QGCCorePlugin.h"
#include "AppSettings.h"
#include "SettingsManager.h"

QGCPositionManager::QGCPositionManager(QGCApplication* app, QGCToolbox* toolbox)
    : QGCTool           (app, toolbox)
    , _updateInterval   (0)
    , _gcsHeading       (NAN)
    , _currentSource    (NULL)
    , _defaultSource    (NULL)
    , _nmeaSource       (NULL)
    , _simulatedSource  (NULL)
    , _landingPadSource (NULL)
{
}

QGCPositionManager::~QGCPositionManager()
{
    delete(_simulatedSource);
    delete(_nmeaSource);
}

void QGCPositionManager::settingsChanged()
{
    bool previous_setting = _sendPlanckGPS;
    _sendPlanckGPS = qgcApp()->toolbox()->settingsManager()->appSettings()->sendPlanckGPS()->rawValue().toBool();

    //Check the position source.
    if(previous_setting != _sendPlanckGPS) {
        //If QGC is emitting the landing_platform state message, the source needs to be
        //either NMEA or internal.  Otherwise it should be the LandingPad, meaning something
        //else is sending position update messages
        if(_sendPlanckGPS) {
            if(_nmeaSource) {
                setPositionSource(QGCPositionSource::NmeaGPS);
            } else {
                setPositionSource(QGCPositionSource::InternalGPS);
            }
        } else {
            setPositionSource(QGCPositionSource::LandingPad);
        }
    }
}

void QGCPositionManager::setToolbox(QGCToolbox *toolbox)
{
   QGCTool::setToolbox(toolbox);
   //-- First see if plugin provides a position source
   _defaultSource = toolbox->corePlugin()->createPositionSource(this);
   if(!_defaultSource) {
       //-- Otherwise, create a default one
       _defaultSource = QGeoPositionInfoSource::createDefaultSource(this);
   }
   _simulatedSource = new SimulatedPosition();
   _landingPadSource = qgcApp()->toolbox()->landingPadManager();

   // Enable this to get a simulated target on desktop
   // if (_defaultSource == nullptr) {
   //     _defaultSource = _simulatedSource;
   // }

   //Is the internal GPS providing Planck position updates?
   if(_sendPlanckGPS) {
       //This can be overrided if/when the NMEA source is used
       setPositionSource(QGCPositionSource::InternalGPS);
   } else {
       setPositionSource(QGCPositionSource::LandingPad);
   }


   connect(toolbox->settingsManager()->appSettings()->sendPlanckGPS(), &Fact::rawValueChanged, this, &QGCPositionManager::settingsChanged);
}

void QGCPositionManager::setNmeaSourceDevice(QIODevice* device)
{
    // stop and release _nmeaSource
    if (_nmeaSource) {
        _nmeaSource->stopUpdates();
        disconnect(_nmeaSource);

        // if _currentSource is pointing there, point to null
        if (_currentSource == _nmeaSource){
            _currentSource = nullptr;
        }

        delete _nmeaSource;
        _nmeaSource = nullptr;

    }
    _nmeaSource = new QNmeaPositionInfoSource(QNmeaPositionInfoSource::RealTimeMode, this);
    _nmeaSource->setDevice(device);
    setPositionSource(QGCPositionManager::NmeaGPS);
}

void QGCPositionManager::_positionUpdated(const QGeoPositionInfo &update)
{
    QGeoCoordinate newGCSPosition = QGeoCoordinate();
    qreal newGCSHeading = update.attribute(QGeoPositionInfo::Direction);

    if (update.isValid()) {
        // Note that gcsPosition filters out possible crap values
        if (qAbs(update.coordinate().latitude()) > 0.001 && qAbs(update.coordinate().longitude()) > 0.001) {
            newGCSPosition = update.coordinate();
        }
    }

    //Send the planck landing state position if necessary
    if(_currentSource != nullptr && _sendPlanckGPS)
    {
        sendMessageToVehicle();
    }

    if (newGCSPosition != _gcsPosition) {
        _gcsPosition = newGCSPosition;
        emit gcsPositionChanged(_gcsPosition);
    }
    if (newGCSHeading != _gcsHeading) {
        _gcsHeading = newGCSHeading;
        emit gcsHeadingChanged(_gcsHeading);
    }

    emit positionInfoUpdated(update);
}

int QGCPositionManager::updateInterval() const
{
    return _updateInterval;
}

void QGCPositionManager::setPositionSource(QGCPositionManager::QGCPositionSource source)
{
    if (_currentSource != nullptr) {
        _currentSource->stopUpdates();
        disconnect(_currentSource);
    }

    if (qgcApp()->runningUnitTests()) {
        // Units test on travis fail due to lack of position source
        return;
    }

    switch(source) {
    case QGCPositionManager::Log:
        break;
    case QGCPositionManager::Simulated:
        _currentSource = _simulatedSource;
        break;
    case QGCPositionManager::LandingPad:
        _currentSource = _landingPadSource;
        break;
    case QGCPositionManager::NmeaGPS:
        _currentSource = _nmeaSource;
        break;
    case QGCPositionManager::InternalGPS:
    default:        
        _currentSource = _defaultSource;
        break;
    }

    if (_currentSource != nullptr) {
        _updateInterval = _currentSource->minimumUpdateInterval();
        _currentSource->setPreferredPositioningMethods(QGeoPositionInfoSource::SatellitePositioningMethods);
        _currentSource->setUpdateInterval(_updateInterval);
        connect(_currentSource, &QGeoPositionInfoSource::positionUpdated,       this, &QGCPositionManager::_positionUpdated);
        connect(_currentSource, SIGNAL(error(QGeoPositionInfoSource::Error)),   this, SLOT(_error(QGeoPositionInfoSource::Error)));
        _currentSource->startUpdates();
    }
}

void QGCPositionManager::_error(QGeoPositionInfoSource::Error positioningError)
{
    qWarning() << "QGCPositionManager error" << positioningError;
}

void QGCPositionManager::sendMessageToVehicle()
{
    QmlObjectListModel& vehicles = *_toolbox->multiVehicleManager()->vehicles();
    MAVLinkProtocol* mavlinkProtocol = _toolbox->mavlinkProtocol();
    for (int i = 0; i < vehicles.count(); i++) {
        Vehicle* vehicle = qobject_cast<Vehicle*>(vehicles[i]);
        mavlink_message_t message;
        mavlink_planck_landing_platform_state_t msg;
        msg.latitude = (int32_t)(_gcsPosition.latitude()*1.E7);
        msg.longitude = (int32_t)(_gcsPosition.longitude()*1.E7);
        msg.altitude = (int32_t)(_gcsPosition.altitude()*1.E3);
        msg.roll = msg.pitch = msg.yaw = msg.vn = msg.ve = msg.vd = 0;
        mavlink_msg_planck_landing_platform_state_encode_chan(mavlinkProtocol->getSystemId(),
                                              mavlinkProtocol->getComponentId(),
                                              vehicle->priorityLink()->mavlinkChannel(),
                                              &message,
                                              &msg);
        vehicle->sendMessageOnLink(vehicle->priorityLink(), message);
    }
}
