#pragma once
#include <QObject>
#include "COTProtocol.h"
#include "QGCToolbox.h"
#include "QTcpSocket"
#include "QTimer"
#include <QGeoPositionInfo>

class LinkInterface;

class COTTranslator : public QGCTool
{
  Q_OBJECT
public:
  COTTranslator(QGCApplication* app, QGCToolbox* toolbox);
  ~COTTranslator();
  virtual void setToolbox(QGCToolbox *toolbox);

  Q_PROPERTY(QGeoCoordinate COTTargetPosition  READ targetPosition NOTIFY targetPositionChanged)

  QGeoCoordinate targetPosition (void){ return _targetPosition; };

signals:
  void targetPositionChanged(QGeoCoordinate position);

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
  QGeoCoordinate _targetPosition;
};
