#ifndef PLANCKLISTENER_H
#define PLANCKLISTENER_H

#include <QObject>
#include <QTimer>
#include "QGCToolbox.h"
#include <mavlink.h>
#include <QUdpSocket>

class LinkInterface;

class PlanckListener : public QGCTool
{
    Q_OBJECT
public:
    PlanckListener(QGCApplication* app, QGCToolbox* toolbox);

    // Override from QGCTool
    virtual void setToolbox(QGCToolbox *toolbox);
    Q_PROPERTY(bool TagHealth  READ TagHealth  NOTIFY HealthChanged)
    Q_PROPERTY(bool BoatHealth READ BoatHealth  NOTIFY HealthChanged)
    Q_PROPERTY(int ChargerState  READ getChargerState NOTIFY chargerChanged)
    Q_PROPERTY(int takeoffReadyState READ takeoffReadyState NOTIFY takeoffReadyStateChanged)
    Q_INVOKABLE void toggleCharger();

    enum ChargerState {
        CHARGER_OFF = 0,
        CHARGER_ON = 1,
        CHARGER_REQUESTED = 2
    };

    bool TagHealth() { return tag_health; }
    bool BoatHealth() { return boat_health; }
    ChargerState getChargerState();
    void setCharger(bool on);
    int takeoffReadyState();
signals:
    void HealthChanged();
    void chargerChanged();
    void takeoffReadyStateChanged();

public slots:
    void onMAVLinkMessage(LinkInterface* link, mavlink_message_t message);
    void onHealthTimeout();

private:
    QTimer health_timer;
    bool tag_health;
    bool boat_health;
    ChargerState charger_on;
    int takeoff_ready_state;

    // These are the relay commands https://ncd.io/proxr-quick-start-guide/
    // R1: on: 0x6C, off: 0x64
    // R2: on: 0x6D, off: 0x65
    // R3: on: 0x6E, off: 0x66
    // R4: on: 0x6F, off: 0x67
    //
    // On the LARS:
    // Relay1: charger
    // Relay2: retract
    // Relay3: extend
    enum class Relay : uint8_t {
      R1_ON   = 0x6C,
      R1_OFF  = 0x64,
      R1_READ = 0x74,
      R2_ON   = 0x6D,
      R2_OFF  = 0x65,
      R2_READ = 0x75,
      R3_ON   = 0x6E,
      R3_OFF  = 0x66,
      R3_READ = 0x76,
      R4_ON   = 0x6F,
      R4_OFF  = 0x67,
      R4_READ = 0x77,
      ALL_OFF = 0x81,
      ALL_ON  = 0x82,
      ALL_READ = 0x7C,
    };

    // Structure from Turning Individual Relays On/ Off in Selected Relay Banks (section 2.5)
    struct buf_t {
      struct data_t {
        uint8_t header;
        uint8_t payload_len;
        uint8_t p1;
        uint8_t relay;
        uint8_t bank;
        uint8_t checksum;
      };
      union{
        uint8_t bytes[6];
        data_t data;
      };
      buf_t(const Relay &r)
      {
        data.header = 0xAA;
        data.payload_len = 0x03;
        data.p1 = 0xFE;
        data.relay = (uint8_t) r;
        data.bank = 0x01;
        update_checksum();
      };
      void update_checksum() {
        uint64_t sum = 0;
        for(int i=0; i<sizeof(bytes)-1; ++i) {
          sum += bytes[i];
        }
        data.checksum = uint8_t(sum & 0x000000FF);
      };
    };

    QUdpSocket udp;
    QHostAddress relay_host_address;
    int relay_host_port;
    QTimer request_timer;
    void sendChargerOnOffCommand(bool on);
    void readDatagrams();
    void chargerRequest();
};

#endif // PLANCKLISTENER_H
