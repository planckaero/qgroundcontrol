#include "FollowTargetMonitor.h"
#include "LinkInterface.h"
#include "MAVLinkProtocol.h"
#include "MultiVehicleManager.h"

#include <iostream>

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

bool FollowTargetMonitor::get_target_status()
{
    return target_available;
}


void FollowTargetMonitor::onMAVLinkMessage(LinkInterface* link, mavlink_message_t message)
{
    Q_UNUSED(link);

    if(message.msgid == MAVLINK_MSG_ID_GLOBAL_POSITION_INT && message.sysid != active_vehicle_sysid) {
        if(!target_available) {
            emit target_status_changed();
        }
        target_available = true;
        target_timer.start(3000);
    }
}

void FollowTargetMonitor::onTargetTimeout()
{
    target_available = false;
    emit target_status_changed();
    target_timer.stop();
}

void FollowTargetMonitor::onActiveVehicleChanged(Vehicle* vehicle)
{
    active_vehicle_sysid = (vehicle) ? vehicle->id() : -1;
}
