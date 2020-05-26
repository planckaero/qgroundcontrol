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

    //Decode this if necessary
    if(message.msgid == MAVLINK_MSG_ID_COPILOTING_CUSTOM)
    {
        mavlink_copiloting_custom_t co_msg;
        mavlink_msg_copiloting_custom_decode(&message, &co_msg);

        //Turn the payload into a mavlink message
        if(co_msg.len <= MAVLINK_MAX_PACKET_LEN) {
            mavlink_message_t payload_message;
            mavlink_status_t mav_status;
            for(int i=0; i<(int)co_msg.len; ++i) {
                if(mavlink_parse_char(0, co_msg.data[i], &payload_message, &mav_status) == MAVLINK_FRAMING_OK) {
                    message = payload_message;
                }
            }
        }
    }

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

