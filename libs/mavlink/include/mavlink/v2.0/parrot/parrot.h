/** @file
 *  @brief MAVLink comm protocol generated from parrot.xml
 *  @see http://mavlink.org
 */
#pragma once
#ifndef MAVLINK_PARROT_H
#define MAVLINK_PARROT_H

#ifndef MAVLINK_H
    #error Wrong include order: MAVLINK_PARROT.H MUST NOT BE DIRECTLY USED. Include mavlink.h from the same directory instead or set ALL AND EVERY defines from MAVLINK.H manually accordingly, including the #define MAVLINK_H call.
#endif

#undef MAVLINK_THIS_XML_IDX
#define MAVLINK_THIS_XML_IDX 5

#ifdef __cplusplus
extern "C" {
#endif

// MESSAGE LENGTHS AND CRCS

#ifndef MAVLINK_MESSAGE_LENGTHS
#define MAVLINK_MESSAGE_LENGTHS {}
#endif

#ifndef MAVLINK_MESSAGE_CRCS
#define MAVLINK_MESSAGE_CRCS {{40001, 190, 132, 132, 0, 0, 0}}
#endif

#include "../protocol.h"

#define MAVLINK_ENABLED_PARROT

// ENUM DEFINITIONS


/** @brief Type of the view mode. This is how the vehicle should behave to set its orientation. */
#ifndef HAVE_ENUM_MAV_VIEW_MODE_TYPE
#define HAVE_ENUM_MAV_VIEW_MODE_TYPE
typedef enum MAV_VIEW_MODE_TYPE
{
   VIEW_MODE_TYPE_ABSOLUTE=0, /* Vehicle orientation is fixed between two waypoints. Orientation is changed when the waypoint is validated | */
   VIEW_MODE_TYPE_CONTINUE=1, /* Vehicle orientation changes linearly between two waypoints. | */
   VIEW_MODE_TYPE_ROI=2, /* Vehicle orientation is given by a ROI. | */
   MAV_VIEW_MODE_TYPE_ENUM_END=3, /*  | */
} MAV_VIEW_MODE_TYPE;
#endif

/** @brief Type of still capture that is performed upon a still capture initiation. */
#ifndef HAVE_ENUM_MAV_STILL_CAPTURE_MODE_TYPE
#define HAVE_ENUM_MAV_STILL_CAPTURE_MODE_TYPE
typedef enum MAV_STILL_CAPTURE_MODE_TYPE
{
   STILL_CAPTURE_MODE_TYPE_TIMELAPSE=0, /* Timelapse capture. | */
   STILL_CAPTURE_MODE_TYPE_GPS_POSITION=1, /* Capture according to the GPS position of the vehicle. Images are captured with an equal spacing. | */
   STILL_CAPTURE_MODE_TYPE_AUTOMATIC_OVERLAP=2, /* Capture according to an overlap rate. Images captured will overlap each other by a percentage defined by the overlap rate. | */
   MAV_STILL_CAPTURE_MODE_TYPE_ENUM_END=3, /*  | */
} MAV_STILL_CAPTURE_MODE_TYPE;
#endif

/** @brief These flags encode the photo sensors. */
#ifndef HAVE_ENUM_MAV_PHOTO_SENSORS_FLAG
#define HAVE_ENUM_MAV_PHOTO_SENSORS_FLAG
typedef enum MAV_PHOTO_SENSORS_FLAG
{
   MAV_PHOTO_SENSORS_FLAG_RGB=1, /* 0x01 RGB sensor. | */
   MAV_PHOTO_SENSORS_FLAG_GREEN_BAND=2, /* 0x02 Green band sensor. | */
   MAV_PHOTO_SENSORS_FLAG_RED_BAND=4, /* 0x04 Red band sensor. | */
   MAV_PHOTO_SENSORS_FLAG_RED_EDGE_BAND=8, /* 0x08 Red-edge band sensor. | */
   MAV_PHOTO_SENSORS_FLAG_NEAR_IR_BAND=16, /* 0x10 Near-infrared band sensor. | */
   MAV_PHOTO_SENSORS_FLAG_ENUM_END=17, /*  | */
} MAV_PHOTO_SENSORS_FLAG;
#endif

// MAVLINK VERSION

#ifndef MAVLINK_VERSION
#define MAVLINK_VERSION 2
#endif

#if (MAVLINK_VERSION == 0)
#undef MAVLINK_VERSION
#define MAVLINK_VERSION 2
#endif

// MESSAGE DEFINITIONS
#include "./mavlink_msg_copiloting_custom.h"

// base include


#undef MAVLINK_THIS_XML_IDX
#define MAVLINK_THIS_XML_IDX 5

#if MAVLINK_THIS_XML_IDX == MAVLINK_PRIMARY_XML_IDX
# define MAVLINK_MESSAGE_INFO {MAVLINK_MESSAGE_INFO_COPILOTING_CUSTOM}
# define MAVLINK_MESSAGE_NAMES {{ "COPILOTING_CUSTOM", 40001 }}
# if MAVLINK_COMMAND_24BIT
#  include "../mavlink_get_info.h"
# endif
#endif

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MAVLINK_PARROT_H
