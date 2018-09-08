/****************************************************************************
 *
 *   (c) 2009-2016 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#include "AirMapTrafficMonitor.h"
#include "AirMapManager.h"

#include <QDateTime>

using namespace airmap;

//-----------------------------------------------------------------------------
AirMapTrafficMonitor::AirMapTrafficMonitor(AirMapSharedState& shared)
    : _shared(shared)
{
}

//-----------------------------------------------------------------------------
AirMapTrafficMonitor::~AirMapTrafficMonitor()
{
    stop();
}

//-----------------------------------------------------------------------------
void
AirMapTrafficMonitor::startConnection(const QString& flightID)
{
    if(flightID.isEmpty() || _flightID == flightID) {
        return;
    }
    qCDebug(AirMapManagerLog) << QDateTime::currentDateTimeUtc() << "Traffic update started for" << flightID << _flightID;
    _flightID = flightID;
    std::weak_ptr<LifetimeChecker> isAlive(_instance);
    auto handler = [this, isAlive](const Traffic::Monitor::Result& result) {
        if (!isAlive.lock()) return;
        if (result) {
            _monitor = result.value();
            _subscriber = std::make_shared<Traffic::Monitor::FunctionalSubscriber>(
                    std::bind(&AirMapTrafficMonitor::_update, this, std::placeholders::_1,  std::placeholders::_2));
            _monitor->subscribe(_subscriber);
        } else {
            QString description = QString::fromStdString(result.error().description() ? result.error().description().get() : "");
            emit error("Failed to start Traffic Monitoring",
                    QString::fromStdString(result.error().message()), description);
        }
    };
    Traffic::Monitor::Params params{flightID.toStdString(), _shared.loginToken().toStdString()};
    _shared.client()->traffic().monitor(params, handler);
}

//-----------------------------------------------------------------------------
void
AirMapTrafficMonitor::_update(Traffic::Update::Type type, const std::vector<Traffic::Update>& update)
{
    qCDebug(AirMapManagerLog) << QDateTime::currentDateTimeUtc() << "Traffic update with" << update.size() << "elements";
    if (type != Traffic::Update::Type::situational_awareness)
        return; // currently we're only interested in situational awareness
    for (const auto& traffic : update) {
        QString traffic_id = QString::fromStdString(traffic.id);
        QString vehicle_id = QString::fromStdString(traffic.aircraft_id);
        emit trafficUpdate(type == Traffic::Update::Type::alert, traffic_id, vehicle_id,
            QGeoCoordinate(traffic.latitude, traffic.longitude, traffic.altitude), static_cast<float>(traffic.heading));
    }
}

//-----------------------------------------------------------------------------
void
AirMapTrafficMonitor::stop()
{
    if (_monitor) {
        qCDebug(AirMapManagerLog) << "Traffic update stopped for" << _flightID;
        _monitor->unsubscribe(_subscriber);
        _subscriber.reset();
        _monitor.reset();
        _flightID.clear();
    }
}

