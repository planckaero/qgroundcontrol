#include "COTTranslator.h"
#include <iostream>
#include <unistd.h>
#include "MAVLinkProtocol.h"
#include "LinkInterface.h"

COTTranslator::COTTranslator(QGCApplication* app, QGCToolbox* toolbox) : QGCTool(app, toolbox) {
    Init();
}

COTTranslator::~COTTranslator() {
    socket.close();
}

void COTTranslator::setToolbox(QGCToolbox *toolbox)
{
    QGCTool::setToolbox(toolbox);
    connect(toolbox->mavlinkProtocol(), &MAVLinkProtocol::messageReceived, this, &COTTranslator::onMAVLinkMessage);
}

bool COTTranslator::Init()
{
    connect(&socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(&socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(&socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(&socket, SIGNAL(readyRead()),this, SLOT(readyRead()));

    qDebug() << "connecting...";

    // this is not blocking call
    //socket.connectToHost("192.168.42.2", 6969);
    socket.connectToHost("127.0.0.1", 6969);

    // we need to wait...
    if(!socket.waitForConnected(5000))
    {
        qDebug() << "Error: " << socket.errorString();
        return false;
    }
    return true;
}

// Called when a properly aligned MAVLink message is detected
void COTTranslator::onMAVLinkMessage(LinkInterface* link, mavlink_message_t message) {
  Q_UNUSED(link);
  std::string cot_message = cot_proto.TranslateMessage(&message);
  if(cot_message!="")// && cot_msg_detected)
  {
      socket.write(cot_message.c_str());
  }
}

// Called when a packet comes in on the COT listen port
void COTTranslator::OnCOTData(void* data, int length)
{
  cot_msg_detected = true;
  if(cot_proto.Parse(data, length))
  {
    if(cot_proto.IsPingMessage())
    {
      // I'm rubber, you're glue.
      socket.write((const char*)data, length);
    }
    else
    {
      cot_proto.Process();
    }
  }
}

void COTTranslator::connected()
{
    qDebug() << "connected...";
}

void COTTranslator::disconnected()
{
    qDebug() << "disconnected...";
}

void COTTranslator::bytesWritten(qint64 bytes)
{
    qDebug() << bytes << " bytes written...";
}

void COTTranslator::readyRead()
{
    qDebug() << "reading...";

    // read the data from the socket
    QByteArray data = socket.readAll();
    OnCOTData(data.data_ptr(), data.length());
}
