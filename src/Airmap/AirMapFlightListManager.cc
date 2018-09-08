/****************************************************************************
 *
 *   (c) 2017 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/


#include "AirMapManager.h"
#include "AirMapFlightListManager.h"

#include "airmap/flights.h"
#include "airmap/pilots.h"
#include "airmap/geometry.h"

using namespace airmap;

//-----------------------------------------------------------------------------
AirMapFlightInfo::AirMapFlightInfo(const airmap::Flight& flight, QObject *parent)
    : AirspaceFlightInfo(parent)
    , _flight(flight)
{
    //-- Load bounding box geometry
    const Geometry& geometry = flight.geometry;
    if(geometry.type() == Geometry::Type::polygon) {
        const Geometry::Polygon& polygon = geometry.details_for_polygon();
        for (const auto& vertex :  polygon.outer_ring.coordinates) {
            QGeoCoordinate coord;
            if (vertex.altitude) {
                coord = QGeoCoordinate(vertex.latitude, vertex.longitude, vertex.altitude.get());
            } else {
                coord = QGeoCoordinate(vertex.latitude, vertex.longitude);
            }
            _boundingBox.append(QVariant::fromValue(coord));
        }
    }
}

//-----------------------------------------------------------------------------
QString
AirMapFlightInfo::createdTime()
{
    return QDateTime::fromMSecsSinceEpoch(static_cast<qint64>(airmap::milliseconds_since_epoch(_flight.created_at))).toString("yyyy MM dd - hh:mm:ss");
}

//-----------------------------------------------------------------------------
QString
AirMapFlightInfo::startTime()
{
    return QDateTime::fromMSecsSinceEpoch(static_cast<qint64>(airmap::milliseconds_since_epoch(_flight.start_time))).toString("yyyy MM dd - hh:mm:ss");
}

//-----------------------------------------------------------------------------
QDateTime
AirMapFlightInfo::qStartTime()
{
    return QDateTime::fromMSecsSinceEpoch(static_cast<qint64>(airmap::milliseconds_since_epoch(_flight.start_time)));
}

//-----------------------------------------------------------------------------
bool
AirMapFlightInfo::active()
{
    QDateTime end = QDateTime::fromMSecsSinceEpoch(static_cast<qint64>(airmap::milliseconds_since_epoch(_flight.end_time)));
    QDateTime now = QDateTime::currentDateTime();
    return end > now;
}

//-----------------------------------------------------------------------------
void
AirMapFlightInfo::setEndFlight(DateTime end)
{
    _flight.end_time = end;
    emit activeChanged();
}

//-----------------------------------------------------------------------------
QString
AirMapFlightInfo::endTime()
{
    return QDateTime::fromMSecsSinceEpoch(static_cast<qint64>(airmap::milliseconds_since_epoch(_flight.end_time))).toString("yyyy MM dd - hh:mm:ss");
}

//-----------------------------------------------------------------------------
AirMapFlightListManager::AirMapFlightListManager(AirMapSharedState& shared, QObject *parent)
    : AirspaceFlightListProvider(parent)
    , _shared(shared)
{
}

//-----------------------------------------------------------------------------
void
AirMapFlightListManager::endFlight(QString flightID)
{
    qCDebug(AirMapManagerLog) << "End flight";
    _flightToEnd = flightID;
    if (_shared.pilotID().isEmpty()) {
        //-- Need to get the pilot id
        qCDebug(AirMapManagerLog) << "Getting pilot ID";
        _state = State::GetPilotID;
        std::weak_ptr<LifetimeChecker> isAlive(_instance);
        _shared.doRequestWithLogin([this, isAlive](const QString& login_token) {
            if (!isAlive.lock()) return;
            Pilots::Authenticated::Parameters params;
            params.authorization = login_token.toStdString();
            _shared.client()->pilots().authenticated(params, [this, isAlive](const Pilots::Authenticated::Result& result) {
                if (!isAlive.lock()) return;
                if (_state != State::GetPilotID) return;
                if (result) {
                    QString pilotID = QString::fromStdString(result.value().id);
                    _shared.setPilotID(pilotID);
                    qCDebug(AirMapManagerLog) << "Got Pilot ID:" << pilotID;
                    _state = State::Idle;
                    _endFlight();
                } else {
                    _state = State::Idle;
                    QString description = QString::fromStdString(result.error().description() ? result.error().description().get() : "");
                    emit error("Failed to get pilot ID", QString::fromStdString(result.error().message()), description);
                    return;
                }
            });
        });
    } else {
        _endFlight();
    }
}

//-----------------------------------------------------------------------------
void
AirMapFlightListManager::_endFlight()
{
    if(_flightToEnd.isEmpty()) {
        qCDebug(AirMapManagerLog) << "End non existing flight";
        return;
    }
    qCDebug(AirMapManagerLog) << "End Flight. State:" << static_cast<int>(_state);
    if(_state != State::Idle) {
        QTimer::singleShot(100, this, &AirMapFlightListManager::_endFlight);
        return;
    }
    qCDebug(AirMapManagerLog) << "Ending flight:" << _flightToEnd;
    _state = State::FlightEnd;
    std::weak_ptr<LifetimeChecker> isAlive(_instance);
    Flights::EndFlight::Parameters params;
    params.authorization = _shared.loginToken().toStdString();
    params.id = _flightToEnd.toStdString();
    //-- End flight
    _shared.client()->flights().end_flight(params, [this, isAlive](const Flights::EndFlight::Result& result) {
        if (!isAlive.lock()) return;
        if (_state != State::FlightEnd) return;
        if (result) {
            qCDebug(AirMapManagerLog) << "Flight Ended";
            int idx = _flightList.findFlightID(_flightToEnd);
            if(idx >= 0) {
                AirMapFlightInfo* pInfo = qobject_cast<AirMapFlightInfo*>(_flightList.get(idx));
                if(pInfo) {
                    pInfo->setEndFlight(result.value().end_time);
                }
            }
        } else {
            QString description = QString::fromStdString(result.error().description() ? result.error().description().get() : "");
            emit error("End flight failed", QString::fromStdString(result.error().message()), description);
        }
        _flightToEnd.clear();
        _state = State::Idle;
    });
}

//-----------------------------------------------------------------------------
void
AirMapFlightListManager::loadFlightList(QDateTime startTime, QDateTime endTime)
{
    //-- TODO: This is not checking if the state is Idle. Again, these need to
    //   queued up and handled by a worker thread.
    qCDebug(AirMapManagerLog) << "Preparing load flight list";
    _loadingFlightList = true;
    emit loadingFlightListChanged();
    _rangeStart = startTime;
    _rangeEnd   = endTime;
    qCDebug(AirMapManagerLog) << "List flights from:" << _rangeStart.toString("yyyy MM dd - hh:mm:ss") << "to" << _rangeEnd.toString("yyyy MM dd - hh:mm:ss");
    if (_shared.pilotID().isEmpty()) {
        //-- Need to get the pilot id
        qCDebug(AirMapManagerLog) << "Getting pilot ID";
        _state = State::GetPilotID;
        std::weak_ptr<LifetimeChecker> isAlive(_instance);
        _shared.doRequestWithLogin([this, isAlive](const QString& login_token) {
            if (!isAlive.lock()) return;
            Pilots::Authenticated::Parameters params;
            params.authorization = login_token.toStdString();
            _shared.client()->pilots().authenticated(params, [this, isAlive](const Pilots::Authenticated::Result& result) {
                if (!isAlive.lock()) return;
                if (_state != State::GetPilotID) return;
                if (result) {
                    QString pilotID = QString::fromStdString(result.value().id);
                    _shared.setPilotID(pilotID);
                    qCDebug(AirMapManagerLog) << "Got Pilot ID:" << pilotID;
                    _state = State::Idle;
                    _loadFlightList();
                } else {
                    _state = State::Idle;
                    QString description = QString::fromStdString(result.error().description() ? result.error().description().get() : "");
                    emit error("Failed to get pilot ID", QString::fromStdString(result.error().message()), description);
                    _loadingFlightList = false;
                    emit loadingFlightListChanged();
                    return;
                }
            });
        });
    } else {
        _loadFlightList();
    }
}

//-----------------------------------------------------------------------------
void
AirMapFlightListManager::_loadFlightList()
{
    qCDebug(AirMapManagerLog) << "Load flight list. State:" << static_cast<int>(_state);
    if(_state != State::Idle) {
        QTimer::singleShot(100, this, &AirMapFlightListManager::_loadFlightList);
        return;
    }
    _flightList.clear();
    emit flightListChanged();
    _state = State::LoadFlightList;
    std::weak_ptr<LifetimeChecker> isAlive(_instance);
    _shared.doRequestWithLogin([this, isAlive](const QString& login_token) {
        if (!isAlive.lock()) return;
        if (_state != State::LoadFlightList) return;
        Flights::Search::Parameters params;
        params.authorization = login_token.toStdString();
        quint64 start   = static_cast<quint64>(_rangeStart.toUTC().toMSecsSinceEpoch());
        quint64 end     = static_cast<quint64>(_rangeEnd.toUTC().toMSecsSinceEpoch());
        params.start_after  = airmap::from_milliseconds_since_epoch(airmap::milliseconds(static_cast<long long>(start)));
        params.start_before = airmap::from_milliseconds_since_epoch(airmap::milliseconds(static_cast<long long>(end)));
        params.limit    = 250;
        params.pilot_id = _shared.pilotID().toStdString();
        _shared.client()->flights().search(params, [this, isAlive](const Flights::Search::Result& result) {
            if (!isAlive.lock()) return;
            if (_state != State::LoadFlightList) return;
            if (result && result.value().flights.size() > 0) {
                const Flights::Search::Response& response = result.value();
                for (const auto& flight : response.flights) {
                    AirMapFlightInfo* pFlight = new AirMapFlightInfo(flight, this);
                    _flightList.append(pFlight);
                    qCDebug(AirMapManagerLog) << "Found:" << pFlight->flightID() << pFlight->flightPlanID() << pFlight->endTime();
                }
                _flightList.sortStartFlight();
                emit flightListChanged();
            } else {
                if(!result) {
                    QString description = QString::fromStdString(result.error().description() ? result.error().description().get() : "");
                    emit error("Flight search failed", QString::fromStdString(result.error().message()), description);
                }
            }
            _state = State::Idle;
            _loadingFlightList = false;
            emit loadingFlightListChanged();
        });
    });
}

