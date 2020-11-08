#include "COTTranslator.h"
#include <iostream>
#include <unistd.h>
#include "MAVLinkProtocol.h"
#include "LinkInterface.h"
#include "QMetaObject"

COTTranslator::COTTranslator(QGCApplication* app, QGCToolbox* toolbox) : QGCTool(app, toolbox), reconnect_timer(this) {
    connect(&socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(&socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(&socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
    connect(&socket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(error(QAbstractSocket::SocketError)));
    reconnect_timer.setInterval(1000);
    connect(&reconnect_timer, SIGNAL(timeout()), this, SLOT(connectToHost()));
    reconnect_timer.start();
}

COTTranslator::~COTTranslator() {
    socket.close();
}

void COTTranslator::setToolbox(QGCToolbox *toolbox)
{
    QGCTool::setToolbox(toolbox);
    connect(toolbox->mavlinkProtocol(), &MAVLinkProtocol::messageReceived, this, &COTTranslator::onMAVLinkMessage);
}

// Called when a properly aligned MAVLink message is detected
void COTTranslator::onMAVLinkMessage(LinkInterface* link, mavlink_message_t message) {
  Q_UNUSED(link);
  std::string cot_message = cot_proto.TranslateMessage(&message);
  if(!cot_message.empty())
  {
      if(socket.state() == QAbstractSocket::ConnectedState){
        socket.write(cot_message.c_str());
      }
  }
}

// Called when a packet comes in on the COT listen port
void COTTranslator::OnCOTData(QByteArray data)
{
  if(data.length() <= 0) {
      return;
  }

  if(cot_proto.Parse(data.data(), data.length()))
  {
    if(cot_proto.IsPingMessage())
    {
      // I'm rubber, you're glue.
      if(socket.state() == QAbstractSocket::ConnectedState) {
        socket.write(data);
      }
    }
    else
    {
      cot_proto.Process();
    }
  }
}

void COTTranslator::connected()
{
    reconnect_timer.stop();
}

void COTTranslator::disconnected()
{
    reconnect_timer.start();
}

void COTTranslator::connectToHost() {
    reconnect_timer.stop();
    //If we are currently attempting to connect, restart the
    //connection attempt
    if (socket.state() != QAbstractSocket::ConnectedState) {
        socket.abort();
        socket.connectToHost("127.0.0.1", 6969);
        reconnect_timer.start();
    }
}

void COTTranslator::error(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);
    reconnect_timer.start(1000);
}

void COTTranslator::readyRead()
{
    // read the data from the socket
    OnCOTData(socket.readAll());
}
