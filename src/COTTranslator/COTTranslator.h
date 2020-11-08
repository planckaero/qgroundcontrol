#pragma once
#include <QObject>
#include "COTProtocol.h"
#include "QGCToolbox.h"
#include "QTcpSocket"
#include "QTimer"

class LinkInterface;

class COTTranslator : public QGCTool
{
  Q_OBJECT
public:
  COTTranslator(QGCApplication* app, QGCToolbox* toolbox);
  ~COTTranslator();
  virtual void setToolbox(QGCToolbox *toolbox);

public slots:
    void onMAVLinkMessage(LinkInterface* link, mavlink_message_t message);
    void connected();
    void disconnected();
    void readyRead();
    void error(QAbstractSocket::SocketError socketError);
    void connectToHost();

private:
  void OnCOTData(QByteArray data);
  void OnCOTLatLonMessage(double lat, double lon);

  COTProtocol cot_proto;
  QTcpSocket socket;
  QTimer reconnect_timer;
};
