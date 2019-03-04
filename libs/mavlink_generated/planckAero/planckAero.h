/** @file
 *  @brief MAVLink comm protocol generated from planckAero.xml
 *  @see http://mavlink.org
 */
#pragma once
#ifndef MAVLINK_PLANCKAERO_H
#define MAVLINK_PLANCKAERO_H

#ifndef MAVLINK_H
    #error Wrong include order: MAVLINK_PLANCKAERO.H MUST NOT BE DIRECTLY USED. Include mavlink.h from the same directory instead or set ALL AND EVERY defines from MAVLINK.H manually accordingly, including the #define MAVLINK_H call.
#endif

#undef MAVLINK_THIS_XML_IDX
#define MAVLINK_THIS_XML_IDX 4

#ifdef __cplusplus
extern "C" {
#endif

// MESSAGE LENGTHS AND CRCS

#ifndef MAVLINK_MESSAGE_LENGTHS
#define MAVLINK_MESSAGE_LENGTHS {}
#endif

#ifndef MAVLINK_MESSAGE_CRCS
#define MAVLINK_MESSAGE_CRCS {{9001, 190, 72, 3, 68, 69}, {9002, 228, 36, 0, 0, 0}, {9003, 24, 7, 3, 0, 1}, {9004, 72, 53, 3, 50, 51}, {9005, 22, 6, 3, 4, 5}, {9006, 115, 14, 3, 12, 13}, {9007, 208, 6, 3, 4, 5}, {9008, 43, 3, 3, 0, 1}}
#endif

#include "../protocol.h"

#define MAVLINK_ENABLED_PLANCKAERO

// ENUM DEFINITIONS


/** @brief Planck system and component IDs */
#ifndef HAVE_ENUM_PLANCK_SYSTEM_IDS
#define HAVE_ENUM_PLANCK_SYSTEM_IDS
typedef enum PLANCK_SYSTEM_IDS
{
   PLANCK_SYS_ID=1, /*  | */
   PLANCK_GPS_COMP_ID=34, /*  | */
   PLANCK_COT_COMP_ID=69, /*  | */
   PLANCK_CTRL_COMP_ID=90, /*  | */
   PLANCK_SYSTEM_IDS_ENUM_END=91, /*  | */
} PLANCK_SYSTEM_IDS;
#endif

/** @brief Additional data stream for planck data. */
#ifndef HAVE_ENUM_MAV_DATA_STREAM_PLANCK
#define HAVE_ENUM_MAV_DATA_STREAM_PLANCK
typedef enum MAV_DATA_STREAM_PLANCK
{
   MAV_DATA_STREAM_PLANCK_STATEINFO=99, /* Enable Planck stateinfo data | */
   MAV_DATA_STREAM_PLANCK_ENUM_END=100, /*  | */
} MAV_DATA_STREAM_PLANCK;
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
#include "./mavlink_msg_planck_stateinfo.h"
#include "./mavlink_msg_planck_landing_platform_state.h"
#include "./mavlink_msg_planck_status.h"
#include "./mavlink_msg_planck_cmd_msg.h"
#include "./mavlink_msg_planck_start_takeoff.h"
#include "./mavlink_msg_planck_start_return_to_landing_platform.h"
#include "./mavlink_msg_planck_start_land.h"
#include "./mavlink_msg_planck_stop_controlling.h"

// base include


#undef MAVLINK_THIS_XML_IDX
#define MAVLINK_THIS_XML_IDX 4

#if MAVLINK_THIS_XML_IDX == MAVLINK_PRIMARY_XML_IDX
# define MAVLINK_MESSAGE_INFO {MAVLINK_MESSAGE_INFO_PLANCK_STATEINFO, MAVLINK_MESSAGE_INFO_PLANCK_LANDING_PLATFORM_STATE, MAVLINK_MESSAGE_INFO_PLANCK_STATUS, MAVLINK_MESSAGE_INFO_PLANCK_CMD_MSG, MAVLINK_MESSAGE_INFO_PLANCK_START_TAKEOFF, MAVLINK_MESSAGE_INFO_PLANCK_START_RETURN_TO_LANDING_PLATFORM, MAVLINK_MESSAGE_INFO_PLANCK_START_LAND, MAVLINK_MESSAGE_INFO_PLANCK_STOP_CONTROLLING}
# define MAVLINK_MESSAGE_NAMES {{ "PLANCK_CMD_MSG", 9004 }, { "PLANCK_LANDING_PLATFORM_STATE", 9002 }, { "PLANCK_START_LAND", 9007 }, { "PLANCK_START_RETURN_TO_LANDING_PLATFORM", 9006 }, { "PLANCK_START_TAKEOFF", 9005 }, { "PLANCK_STATEINFO", 9001 }, { "PLANCK_STATUS", 9003 }, { "PLANCK_STOP_CONTROLLING", 9008 }}
# if MAVLINK_COMMAND_24BIT
#  include "../mavlink_get_info.h"
# endif
#endif

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MAVLINK_PLANCKAERO_H
