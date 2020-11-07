#pragma once
#include <QObject>
#include "COTProtocol.h"
#include "QGCToolbox.h"
#include "QTcpSocket"

class LinkInterface;

class COTTranslator : public QGCTool
{
  Q_OBJECT
public:
  COTTranslator(QGCApplication* app, QGCToolbox* toolbox);
  ~COTTranslator();
  virtual void setToolbox(QGCToolbox *toolbox);
  bool Init();
  void Run();
  void Stop() { running = false; };

public slots:
    void onMAVLinkMessage(LinkInterface* link, mavlink_message_t message);
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();

private:
  void OnCOTData(void* data, int length);
  void OnCOTLatLonMessage(double lat, double lon);

  COTProtocol cot_proto;
  bool running = true;
  bool cot_msg_detected = false;
  QTcpSocket socket;
};
