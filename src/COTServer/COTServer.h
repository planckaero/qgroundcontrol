#pragma once
#include <QObject>
#include "COTProtocol.h"
#include "QGCToolbox.h"

class COTServer : public QGCTool
{
  Q_OBJECT
public:
  COTServer(QGCApplication* app, QGCToolbox* toolbox);
  ~COTServer();
  virtual void setToolbox(QGCToolbox *toolbox);
  bool Init();
  void Run();
  void Stop() { running = false; };

public slots:
    void onMAVLinkMessage(LinkInterface* link, mavlink_message_t message);

private:
  void OnCOTData(void* data, int length);
  void OnCOTLatLonMessage(double lat, double lon);

  COTProtocol cot_proto;
  bool running = true;
  bool cot_msg_detected = false;
};
