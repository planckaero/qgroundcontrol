#include "COTProtocol.h"
#include <iostream>
#include <string>
#include <vector>

// Example COT message:
// <?xml version="1.0" encoding="UTF-8" standalone="yes"?><event version="2.0" uid="ANDROID-a42924fb-1b8a-4d0c-a9f4-acc17f59b569" type="a-f-G-U-C" time="2017-08-25T17:48:58.163Z" start="2017-08-25T17:48:58.163Z" stale="2017-08-25T17:50:13.163Z" how="m-g"><point lat="32.713073" lon="-117.153362" hae="-11.683718055315616" ce="32" le="9999999"/><detail><takv platform="ATAK-CIV" version="3.5.0.29623"/><contact endpoint="192.168.100.126:4242:tcp" callsign="MATT"/><uid Droid="MATT"/><__group name="Cyan" role="Team Member"/><status battery="91"/><track speed="0.003332774853333831" course="0.0"/><precisionlocation geopointsrc="GPS" altsrc="GPS"/></detail></event>
//

COTProtocol::COTProtocol()
{
}

COTProtocol::~COTProtocol()
{
}

void COTProtocol::Test()
{
  /*std::string test_string = CreateDronePositionMessage(1.234, 2.345, 10, 5.0, 2.3);
  WorkNode node = Parse(test_string.c_str(), test_string.length());
  PushData(node, test_string.c_str(), test_string.length());
  std::cout << test_string << std::endl;*/
}

bool COTProtocol::Parse(const void* data, int length)
{
  std::string input_xml;
  char* temptext = (char*)data;
  input_xml.assign(temptext, length);
  std::vector<char> xml_copy(input_xml.begin(), input_xml.end());
  xml_copy.push_back('\0');

  try
  {
    work_doc.doc.parse<0>(&xml_copy[0]);    // 0 means default parse flags
  }
  catch(std::exception)
  {
    std::cerr << "Parse exception." << std::endl;
    std::cerr << "Message: " << std::string((char*)data,length) << std::endl;
    return false;
  }
  return true;
}

// If a message comes in with a specific contact, call back with coordinates
void COTProtocol::Process()
{
  double lat, lon;
  std::string str_lat, str_lon;
  rapidxml::xml_node<>* out_node;

  // Check for Planck message
  if(FindNode(work_doc.doc.first_node(), "contact", &out_node))
  {
    if(FindAttribute(out_node, "callsign")==SECRET_CONTACT) // Check if they put in the right callsign
    {
      if(FindNode(work_doc.doc.first_node(), "point", &out_node))
      {
        str_lat = FindAttribute(out_node, "lat");
        if(str_lat=="")
          return;
        lat = stod(str_lat);

        str_lon = FindAttribute(out_node, "lon");
        if(str_lon=="")
          return;
        lon = stod(str_lon);

        CallbackLatLon(lat, lon);
      }
    }
  }
}

/*  -- An example COT ping message
<?xml version="1.0"?>
<event
  version="2.0"
  uid="ANDROID-a42924fb-1b8a-4d0c-a9f4-acc17f59b56a-ping"
  type="t-x-c-t"
  time="2018-07-10T00:49:50.000Z"
  start="2018-07-10T00:49:50.000Z"
  stale="2018-07-10T00:50:00.000Z"
  how="m-g">
    <point lat="0" lon="0" hae="0" ce="9999999" le="9999999"/>
  <detail/>
</event>
*/
bool COTProtocol::IsPingMessage()
{
  rapidxml::xml_node<>* out_node;
  // Check for COT ping message (example below)
  if(FindNode(work_doc.doc.first_node(), "event", &out_node))
  {
    std::string str_type = FindAttribute(out_node, "type");
    if(str_type=="t-x-c-t")
    {
      return true;
      //std::cout << "Ping message detected." << std::endl;
    }
  }
  return false;
}

void COTProtocol::Indent(int level)
{
  for(int i=0; i<level; i++)
  {
    std::cout << "  ";
  }
}

// A recursive method to find an XML node within an XML doc
bool COTProtocol::FindNode(rapidxml::xml_node<>* in_node, std::string name, rapidxml::xml_node<>** out_node)
{
  if((std::string)in_node->name() == name)
  {
    *out_node = in_node;
    return true;
  }
  for(rapidxml::xml_node<> *iter = in_node->first_node(); iter; iter = iter->next_sibling())
  {
    if(FindNode(iter, name, out_node))
    {
      return true;
    }
  }
  return false;
}

std::string COTProtocol::FindAttribute(rapidxml::xml_node<>* in_node, std::string name)
{
  for(rapidxml::xml_attribute<> *attr = in_node->first_attribute(); attr; attr = attr->next_attribute())
  {
    if(attr->name()==name)
      return attr->value();
  }
  return "";
}

void COTProtocol::PrintNode(rapidxml::xml_node<> *node, int level)
{
  Indent(level);
  std::cout << "Node: " << node->name() << std::endl;
  PrintAttributes(node, level + 1);
  for(rapidxml::xml_node<> *iter = node->first_node(); iter; iter = iter->next_sibling())
  {
    PrintNode(iter, level+1);
  }
}

void COTProtocol::PrintAttributes(rapidxml::xml_node<> *node, int level)
{
  for(rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute())
  {
    Indent(level);
    std::cout << "Attribute: " << attr->name() << " = " << attr->value() << std::endl;
  }
}

std::string COTProtocol::TranslateMessage(const void* mavlink_msg)
{
  std::string ret = "";
  mavlink_message_t* mav_msg = (mavlink_message_t*)mavlink_msg;

  switch(mav_msg->msgid)
  {
    case MAVLINK_MSG_ID_GLOBAL_POSITION_INT:
    {
      double lat = ((double)mavlink_msg_global_position_int_get_lat(mav_msg))/1.e7;
      double lon = ((double)mavlink_msg_global_position_int_get_lon(mav_msg))/1.e7;
      double alt = mavlink_msg_global_position_int_get_alt(mav_msg)/1.e3;
      double heading = mavlink_msg_global_position_int_get_hdg(mav_msg)/1.e2;
      double speedx = mavlink_msg_global_position_int_get_vx(mav_msg)/1.e2;
      double speedy = mavlink_msg_global_position_int_get_vy(mav_msg)/1.e2;
      double speedz = mavlink_msg_global_position_int_get_vz(mav_msg)/1.e2;
      double speed = speedx*speedx + speedy*speedy + speedz*speedz;
      speed = sqrt(speed);
      ret = CreateDronePositionMessage(lat, lon, alt, speed, heading);
      break;
    }
    case MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE:
    {
      double lat = ((double)mavlink_msg_planck_landing_platform_state_get_latitude(mav_msg))/1.e7;
      double lon = ((double)mavlink_msg_planck_landing_platform_state_get_longitude(mav_msg))/1.e7;
      double alt = mavlink_msg_planck_landing_platform_state_get_altitude(mav_msg)/1.e3;
      double heading = mavlink_msg_planck_landing_platform_state_get_yaw(mav_msg);
      double speedn = mavlink_msg_planck_landing_platform_state_get_vn(mav_msg);
      double speede = mavlink_msg_planck_landing_platform_state_get_ve(mav_msg);
      double speedd = mavlink_msg_planck_landing_platform_state_get_vd(mav_msg);
      double speed = speedn*speedn + speede*speede + speedd*speedd;
      speed = sqrt(speed);
      ret = CreateCommboxPositionMessage(lat, lon, alt, speed, heading);
      break;
    }
    default:
      //std::cerr << "Cannot translate MAVLINK message to CURSOR-ON-TARGET." << std::endl;
      break;
  }

  return ret;
}

std::string COTProtocol::CreateDronePositionMessage(double lat, double lon, double alt, double speed, double heading)
{
  std::string str_lat = std::to_string(lat);
  std::string str_lon = std::to_string(lon);
  std::string str_alt = std::to_string(alt);
  std::string str_speed = std::to_string(speed);
  std::string str_heading = std::to_string(heading);
  std::string time = CreateTimeString(30);

  std::string ret = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>"
    "<event version=\"2.0\" uid=\"PLANCK-ANAFI\" type=\"a-f-A-C-C\" "+time+" how=\"m-g\">"
      "<point lat=\""+str_lat+"\" lon=\""+str_lon+"\" hae=\""+str_alt+"\" ce=\"2\" le=\"2\"/>"
      "<detail/>"
    "</event>";

  return ret;
}

/*
Here is a sample SPOI message (you would use the vehicle UID to tether it back to):

<?xml version='1.0' standalone='yes'?>
	<event how="m-a"
	       stale="2017-09-22T14:53:19.12Z"
	       start="2017-09-22T14:51:19.12Z"
	       time="2017-09-22T14:51:19.12Z"
	       type="b-m-p-s-p-i"
	       uid="SPOI.001"
	       version="2.0">
	  <detail>
	    <link relation="p-p"
	          type="a-f-G-U-U-M-R"
	          uid="Vehicle.000" />
	  </detail>
	  <point ce="122.9"
	         hae="7.7"
	         lat="42.5808178"
	         le="4.9"
	         lon="-71.1631305" />
	</event>

Explanation:

•	how="m-a"= machine – tracker
•	stale="2017-09-22T14:53:19.12Z" = time when the information ceases to be valid
•	start="2017-09-22T14:51:19.12Z" = time when the information will become valid
•	time="2017-09-22T14:51:19.12Z" = time when the information was generated
•	type="b-m-p-s-p-i" = bits-map-point-sensor-point-interest
•	uid=" SPOI.001"= unique identifier for the SPOI
•	version="2.0" = version of CoT schema
•	link > relationship="p-p" = producer (describes relationship between Vehicle and SPOI)
•	link > type="a-f-G-U-U-M-R" = the CoT type of the Vehicle
•	link > uid="Vehicle.000" = the unique identifier of the Vehicle which produced the SPOI
•	ce="122.9" = cylinder radius (meters)
•	hae="7.7"= height above ellipsoid (meters, WGS84)
•	lat="42.5808178" = latitude (decimal degrees, WGS84)
•	le="4.9" = cylinder half-height (meters)
•	lon="-71.1631305" = longitude (decimal degrees, WGS84)
*/
std::string COTProtocol::CreateSensorMessage(double lat, double lon, double alt)
{
  std::string str_lat = std::to_string(lat);
  std::string str_lon = std::to_string(lon);
  std::string str_alt = std::to_string(alt);
  std::string time = CreateTimeString(30);

  std::string ret = "<?xml version=\"1.0\" standalone=\"yes\"?>"
  	"<event how=\"m-a\""
      + time +
      "type=\"b-m-p-s-p-i\""
      "uid=\"PLANCK-CAMERA\""
      "version=\"2.0\">"
  	  "<detail>"
  	    "<link relation=\"p-p\""
          //"type=\"a-f-G-U-U-M-R\""
          "type=\"a-f-A-C-C\""
          "uid=\"PLANCK-ANAFI\"/>"
  	  "</detail>"
  	  "<point "
  	    "lat=\""+str_lat+"\""
        "lon=\""+str_lon+"\"/>"
        "hae=\""+str_alt+"\""
        "ce=\"2.0\"" // cylinder radius
  	    "le=\"5.0\""   // cylinder half-height
  	"</event>";

  return ret;
}

std::string COTProtocol::CreateTargetPositionMessage(uint32_t id, double lat, double lon, double alt, double speed, double heading)
{
  std::string str_id = std::to_string(id);
  std::string str_lat = std::to_string(lat);
  std::string str_lon = std::to_string(lon);
  std::string str_alt = std::to_string(alt);
  std::string str_speed = std::to_string(speed);
  std::string str_heading = std::to_string(heading);
  std::string time = CreateTimeString(30);

  std::string ret = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>"
    "<event version=\"2.0\" uid=\"UNKNOWN-TARGET-"+str_id+"\" type=\"a-u-G\" "+time+" how=\"m-g\">"
      "<point lat=\""+str_lat+"\" lon=\""+str_lon+"\" hae=\""+str_alt+"\" ce=\"2\" le=\"2\"/>"
      "<detail/>"
    "</event>";

  return ret;
}

std::string COTProtocol::CreateCommboxPositionMessage(double lat, double lon, double alt, double speed, double heading)
{
  std::string str_lat = std::to_string(lat);
  std::string str_lon = std::to_string(lon);
  std::string str_alt = std::to_string(alt);
  std::string str_speed = std::to_string(speed);
  std::string str_heading = std::to_string(heading);
  std::string time = CreateTimeString(30);

  std::string ret = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>"
    "<event version=\"2.0\" uid=\"PLANCK-LANDING-PAD\" type=\"a-f-G\" "+time+" how=\"m-g\">"
      "<point lat=\""+str_lat+"\" lon=\""+str_lon+"\" hae=\""+str_alt+"\" ce=\"2\" le=\"2\"/>"
      "<detail/>"
    "</event>";

  return ret;
}

// Return times in a format for cursor-on-target
// This includes time when reported, time when event started, and time when event is considered stale
// This method does not take milliseconds into account and always reports 000.
std::string COTProtocol::CreateTimeString(const uint32_t stale_period) // Input number of seconds before data is considered stale
{
  //const uint stale_period = 30;
  char time_chars[80];
  time_t rawtime, staletime;
  struct tm* ptm;
  std::string ret;

  time(&rawtime); // Get now time
  staletime = rawtime + stale_period; // Calculate when data is stale
  ptm = gmtime(&rawtime); // Get now time in UTC time

  strftime(time_chars, 80, "%FT%T.000Z", ptm); // Format this time into format COT expects
  std::string report_time(time_chars);
  std::string start_time = report_time; // We will make report time and start time the same

  // Now get a UTC representation of when data is stale
  ptm = gmtime(&staletime);
  strftime(time_chars, 80, "%FT%T.000Z", ptm);
  std::string stale_time(time_chars);

  ret = "time=\"" + report_time + "\" start=\"" + start_time + "\" stale=\"" + stale_time + "\"";

  return ret;
}
