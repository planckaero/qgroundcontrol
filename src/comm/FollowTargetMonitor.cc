#include "FollowTargetMonitor.h"
#include "LinkInterface.h"
#include "MAVLinkProtocol.h"
#include "MultiVehicleManager.h"

FollowTargetMonitor::FollowTargetMonitor(QGCApplication* app, QGCToolbox* toolbox)
    : QGCTool(app, toolbox),
      target_available(false),
      target_timer(this),
      active_vehicle_sysid(-1)
{ }

void FollowTargetMonitor::setToolbox(QGCToolbox *toolbox)
{
    QGCTool::setToolbox(toolbox);
    connect(toolbox->mavlinkProtocol(), &MAVLinkProtocol::messageReceived, this, &FollowTargetMonitor::onMAVLinkMessage);
    connect(&target_timer, SIGNAL(timeout()), this, SLOT(onTargetTimeout()));
    connect(toolbox->multiVehicleManager(), &MultiVehicleManager::activeVehicleChanged, this, &FollowTargetMonitor::onActiveVehicleChanged);
}

bool FollowTargetMonitor::get_target_health()
{
    return target_available;
}

QGeoCoordinate FollowTargetMonitor::get_target_position()
{
    return target_position;
}

void FollowTargetMonitor::onMAVLinkMessage(LinkInterface* link, mavlink_message_t message)
{
    Q_UNUSED(link);
    // Do not try to monitor target until active vehicle system ID available
    if(active_vehicle_sysid < 0) {
        return;
    }

    if(message.msgid == MAVLINK_MSG_ID_GLOBAL_POSITION_INT && message.sysid != active_vehicle_sysid) {
        mavlink_global_position_int_t pos;
        mavlink_msg_global_position_int_decode(&message, &pos);

        // Set target position using GLOBAL_POSITION_INT
        target_position.setLatitude(static_cast<double>(pos.lat)/1e7);
        target_position.setLongitude(static_cast<double>(pos.lon)/1e7);
        target_position.setAltitude(static_cast<double>(pos.alt)/1e3);
        emit target_position_changed(target_position);

        // Emit target health changes based on flag
        if(!target_available) {
            target_available = true;
            emit target_health_changed();
        }
        target_timer.start(3000);
    }
}

void FollowTargetMonitor::onTargetTimeout()
{
    target_available = false;
    emit target_health_changed();
    target_timer.stop();
}

void FollowTargetMonitor::onActiveVehicleChanged(Vehicle* vehicle)
{
    active_vehicle_sysid = (vehicle) ? vehicle->id() : -1;
}
