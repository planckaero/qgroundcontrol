#pragma once
#include "rapidxml.hpp"
#include <mavlink.h>
#include <string>

class COTProtocol
{
public:
  class WorkDoc
  {
  public:
    rapidxml::xml_document<> doc;
  };

  COTProtocol();
  ~COTProtocol();
  void Test();
  void SubscribeToLatLon(std::function<void(double lat, double lon)> cb) { CallbackLatLon = cb; };
  bool Parse(const void* data, int length);
  void Process(); // First call parse!
  bool IsPingMessage(); // Ditto!
  std::string TranslateMessage(const void* mavlink_msg);
  std::string CreateDronePositionMessage(double lat, double lon, double alt, double speed, double heading);
  std::string CreateSensorMessage(double lat, double lon, double alt);
  std::string CreateTargetPositionMessage(uint32_t id, double lat, double lon, double alt, double speed, double heading);
  std::string CreateCommboxPositionMessage(double lat, double lon, double alt, double speed, double heading);
private:
  void Indent(int level);
  bool FindNode(rapidxml::xml_node<> *node, std::string name, rapidxml::xml_node<>** out_node);
  std::string FindAttribute(rapidxml::xml_node<>* in_node, std::string name);
  void PrintNode(rapidxml::xml_node<> *node, int level);
  void PrintAttributes(rapidxml::xml_node<> *node, int level);
  std::string CreateTimeString(const uint32_t stale_period);
  std::function<void(double, double)> CallbackLatLon = 0;
  WorkDoc work_doc;
  const std::string SECRET_CONTACT = "planck-goto-19"; // Only listen for messages with this callsign
};
