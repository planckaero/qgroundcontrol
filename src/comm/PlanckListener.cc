#include <QGeoCoordinate>
#include <QGeoPositionInfo>

#include "PlanckListener.h"
#include "LandingPadPosition.h"
#include "LinkInterface.h"
#include "MAVLinkProtocol.h"
#include "QGCApplication.h"

PlanckListener::PlanckListener(QGCApplication* app, QGCToolbox* toolbox)
: QGCTool(app, toolbox)
, health_timer(this)
, tag_health(false)
, boat_health(false)
{
}

void PlanckListener::setToolbox(QGCToolbox *toolbox)
{
    QGCTool::setToolbox(toolbox);
    connect(toolbox->mavlinkProtocol(), &MAVLinkProtocol::messageReceived, this, &PlanckListener::onMAVLinkMessage);
    connect(&health_timer, SIGNAL(timeout()), this, SLOT(onHealthTimeout()));
}

void PlanckListener::onMAVLinkMessage(LinkInterface* link, mavlink_message_t message)
{
    Q_UNUSED(link);

    if(message.msgid == MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE)
    {
        mavlink_planck_landing_platform_state_t lps;
        mavlink_msg_planck_landing_platform_state_decode(&message, &lps);
        LandingPadPosition* pos = qgcApp()->toolbox()->landingPadManager();
        if(pos)
        {
            pos->setPosition(lps.latitude, lps.longitude);
        }
    }
    else if(message.msgid == MAVLINK_MSG_ID_PLANCK_STATUS)
    {
        mavlink_planck_status_t stat;
        mavlink_msg_planck_status_decode(&message, &stat);
        tag_health = (stat.status & 0x01)!=0;
        boat_health = (stat.status & 0x02)!=0;
        emit HealthChanged();
        health_timer.start(3000);
    }
}

void PlanckListener::onHealthTimeout()
{
    tag_health = false;
    boat_health = false;
    emit HealthChanged();
    health_timer.stop();
}

