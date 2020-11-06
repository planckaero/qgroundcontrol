#include "COTServer.h"
#include <iostream>
#include <unistd.h>
#include "MAVLinkProtocol.h"

COTServer::COTServer(QGCApplication* app, QGCToolbox* toolbox) : QGCTool(app, toolbox) {
  //cot_server(std::bind(&COTServer::OnCOTData, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))
}

COTServer::~COTServer()
{
}

void COTServer::setToolbox(QGCToolbox *toolbox)
{
    QGCTool::setToolbox(toolbox);
    connect(toolbox->mavlinkProtocol(), &MAVLinkProtocol::messageReceived, this, &COTServer::OnMAVLinkMessage);
}

bool COTServer::Init()
{
  //Start a TCP server
  //if(!cot_server.Init(server_options.cot_input_port))
    return false;

  return true;
}

// Called when a properly aligned MAVLink message is detected
void COTServer::onMAVLinkMessage(LinkInterface* link, mavlink_message_t message) {
{
  Q_UNUSED(link);
  std::string cot_message = cot_proto.TranslateMessage(message);
  if(cot_message!="" && cot_msg_detected)
  {
    //cot_server.Multicast((void*)cot_message.c_str(), cot_message.length());
  }
}

// Called when a packet comes in on the COT listen port
void COTServer::OnCOTData(void* data, int length)
{
  cot_msg_detected = true;
  if(cot_proto.Parse(data, length))
  {
    if(cot_proto.IsPingMessage())
    {
      // I'm rubber, you're glue.
      //conn.Write(data, length); //send this back
    }
    else
    {
      cot_proto.Process();
    }
  }
}
