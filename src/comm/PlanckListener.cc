#include <QGeoCoordinate>
#include <QGeoPositionInfo>

#include "PlanckListener.h"
#include "LandingPadPosition.h"
#include "LinkInterface.h"
#include "MAVLinkProtocol.h"
#include "QGCApplication.h"
#include "SettingsManager.h"
#include <mavlink.h>

PlanckListener::PlanckListener(QGCApplication* app, QGCToolbox* toolbox)
: QGCTool(app, toolbox)
, health_timer(this)
, tag_health(false)
, boat_health(false)
, charger_on(CHARGER_REQUESTED)
, udp()
, request_timer(this)
{

}

void PlanckListener::setToolbox(QGCToolbox *toolbox)
{
    QGCTool::setToolbox(toolbox);
    connect(toolbox->mavlinkProtocol(), &MAVLinkProtocol::messageReceived, this, &PlanckListener::onMAVLinkMessage);
    connect(&health_timer, SIGNAL(timeout()), this, SLOT(onHealthTimeout()));
    auto appSettings = toolbox->settingsManager()->appSettings();

    relay_host_address = appSettings->larsRelayControlAddress()->rawValue().toString();
    relay_host_port = appSettings->larsRelayControlPort()->rawValue().toInt();
    if(appSettings->enableLARS()->rawValue().toBool()) {
      udp.bind(QHostAddress::AnyIPv4, appSettings->larsRelayListenPort()->rawValue().toInt(), QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
      connect(&udp, &QUdpSocket::readyRead, this, &PlanckListener::readDatagrams);
      request_timer.setSingleShot(false);
      request_timer.setInterval(1000);
      connect(&(this->request_timer), &QTimer::timeout, this, &PlanckListener::chargerRequest);
      request_timer.start();
    }
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
    else if(message.msgid == MAVLINK_MSG_ID_HEARTBEAT && message.compid == 41) { //41 == PLANCK_ANAFI_SUP_COMP_ID
        //Look for the status field to indicate ready state
        mavlink_heartbeat_t hb;
        mavlink_msg_heartbeat_decode(&message, &hb);
        takeoff_ready_state = (int)hb.system_status;
        emit takeoffReadyStateChanged();
    }
}

void PlanckListener::onHealthTimeout()
{
    tag_health = false;
    boat_health = false;
    emit HealthChanged();
    health_timer.stop();
}

int PlanckListener::takeoffReadyState() {
    return takeoff_ready_state;
}

void PlanckListener::toggleCharger() {
    if(charger_on == CHARGER_OFF) {
        setCharger(true);
    } else if (charger_on == CHARGER_ON) {
        setCharger(false);
    }//Don't do anything when pending
}

void PlanckListener::setCharger(bool on)
{
    sendChargerOnOffCommand(on);
    chargerRequest();
    charger_on = CHARGER_REQUESTED;
    emit chargerChanged();
}

PlanckListener::ChargerState PlanckListener::getChargerState() {
    return charger_on;
}

void PlanckListener::sendChargerOnOffCommand(bool on)
{
    buf_t buf(on ? Relay::R1_ON : Relay::R1_OFF);
    //Send 3 times to ensure delivery
    udp.writeDatagram((const char*) &buf.bytes, sizeof(buf.bytes), relay_host_address, relay_host_port);
    udp.writeDatagram((const char*) &buf.bytes, sizeof(buf.bytes), relay_host_address, relay_host_port);
    udp.writeDatagram((const char*) &buf.bytes, sizeof(buf.bytes), relay_host_address, relay_host_port);
}

void PlanckListener::readDatagrams()
{
    while(udp.hasPendingDatagrams()) {
        uint8_t bytes[2564];
        int len = udp.readDatagram((char*)bytes, 256);
        //See https://ncd.io/proxr-quick-start-guide/ "Reading the Status of Relays"

        //check the checksum
        uint64_t sum = 0;
        for(int i=0; i<len-1; ++i) {
          sum += bytes[i];
        }
        uint8_t checksum = uint8_t(sum & 0x000000FF);
        if(checksum == bytes[3]) {
            bool on = (bool)bytes[2];
            charger_on = on ? CHARGER_ON : CHARGER_OFF;
            emit chargerChanged();
        }
    }
}

void PlanckListener::chargerRequest()
{
    buf_t buf(Relay::R1_READ);
    udp.writeDatagram((const char*) &buf.bytes, sizeof(buf.bytes), relay_host_address, relay_host_port);
}
