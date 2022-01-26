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
, charger_on(false)
, udp()
, request_timer(this)
{
    connect(&udp, &QUdpSocket::readyRead, this, &PlanckListener::readDatagrams);

    request_timer.setSingleShot(false);
    request_timer.setInterval(1000);
    connect(&(this->request_timer), &QTimer::timeout, this, &PlanckListener::chargerRequest);
    request_timer.start();
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

void PlanckListener::setCharger(bool on)
{
    charger_on = on;
    sendChargerOnOffCommand(on);
    emit chargerChanged();
}

void PlanckListener::sendChargerOnOffCommand(bool on)
{
    buf_t buf(on ? Relay::R1_ON : Relay::R1_OFF);
    udp.writeDatagram((const char*) &buf.bytes, sizeof(buf.bytes), QHostAddress("192.168.168.7"), 2101);
}

void PlanckListener::readDatagrams()
{
    while(udp.hasPendingDatagrams()) {
        QNetworkDatagram datagram = udp.receiveDatagram();

        //See https://ncd.io/proxr-quick-start-guide/ "Reading the Status of Relays"
        char bytes[4];
        memcpy(bytes, datagram.data().data_ptr(), 4);

        //check the checksum
        uint64_t sum = 0;
        for(int i=0; i<sizeof(bytes)-1; ++i) {
          sum += bytes[i];
        }
        uint8_t checksum = uint8_t(sum & 0x000000FF);
        if(checksum == bytes[3]) {
            charger_on = bytes[2];
            emit chargerChanged();
        }
    }
}

void PlanckListener::chargerRequest()
{
    buf_t buf(Relay::R1_READ);
    udp.writeDatagram((const char*) &buf.bytes, sizeof(buf.bytes), QHostAddress("192.168.168.7"), 2101);
}
