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
#define MAVLINK_MESSAGE_CRCS {{9145, 107, 26, 0, 0, 0}, {9159, 33, 40, 0, 0, 0}, {9190, 67, 44, 3, 0, 1}, {9235, 82, 8, 0, 0, 0}, {9236, 252, 36, 0, 0, 0}, {9237, 133, 22, 3, 20, 21}, {9238, 175, 19, 3, 16, 17}, {9239, 211, 3, 0, 0, 0}, {9240, 149, 2, 0, 0, 0}}
#endif

#include "../protocol.h"

#define MAVLINK_ENABLED_PLANCKAERO

// ENUM DEFINITIONS


/** @brief  */
#ifndef HAVE_ENUM_PLANCK_STATUS_MODE
#define HAVE_ENUM_PLANCK_STATUS_MODE
typedef enum PLANCK_STATUS_MODE
{
   PLANCK_IDLE=0, /*  | */
   PLANCK_TAKEOFF=1, /*  | */
   PLANCK_STAB=2, /*  | */
   PLANCK_RTB=3, /*  | */
   PLANCK_SEARCHING=4, /*  | */
   PLANCK_LAND_READY=5, /*  | */
   PLANCK_LAND=6, /*  | */
   PLANCK_ORBIT=7, /*  | */
   PLANCK_LEAD_FOLLOW=8, /*  | */
   PLANCK_STATUS_MODE_ENUM_END=9, /*  | */
} PLANCK_STATUS_MODE;
#endif

/** @brief These flags encode the MAV mode. */
#ifndef HAVE_ENUM_PLANCK_STATUS_FAILSAFE
#define HAVE_ENUM_PLANCK_STATUS_FAILSAFE
typedef enum PLANCK_STATUS_FAILSAFE
{
   RC_OK=1, /*  | */
   COMMBOX_OK=2, /*  | */
   BATTERY_OK=4, /*  | */
   COMMBOX_GPS_OK=8, /*  | */
   PLANCK_STATUS_FAILSAFE_ENUM_END=9, /*  | */
} PLANCK_STATUS_FAILSAFE;
#endif

/** @brief These flags encode the MAV mode. */
#ifndef HAVE_ENUM_PLANCK_STATUS_CONTROLLER
#define HAVE_ENUM_PLANCK_STATUS_CONTROLLER
typedef enum PLANCK_STATUS_CONTROLLER
{
   TAG_ESTIMATOR_OK=1, /*  | */
   BOAT_ESTIMATOR_OK=2, /*  | */
   PLANCK_STATUS_CONTROLLER_ENUM_END=3, /*  | */
} PLANCK_STATUS_CONTROLLER;
#endif

/** @brief These flags encode the MAV mode. */
#ifndef HAVE_ENUM_PLANCK_TRACKING_TARGET
#define HAVE_ENUM_PLANCK_TRACKING_TARGET
typedef enum PLANCK_TRACKING_TARGET
{
   LANDING_PLATFORM=0, /*  | */
   TARGET=1, /*  | */
   PLANCK_TRACKING_TARGET_ENUM_END=2, /*  | */
} PLANCK_TRACKING_TARGET;
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
#include "./mavlink_msg_state_info.h"
#include "./mavlink_msg_target_state.h"
#include "./mavlink_msg_version_query_response.h"
#include "./mavlink_msg_landing_platform_heartbeat.h"
#include "./mavlink_msg_landing_platform_state.h"
#include "./mavlink_msg_orbit_command.h"
#include "./mavlink_msg_lead_follow_command.h"
#include "./mavlink_msg_planck_status.h"
#include "./mavlink_msg_planck_radio_status.h"

// base include


#undef MAVLINK_THIS_XML_IDX
#define MAVLINK_THIS_XML_IDX 4

#if MAVLINK_THIS_XML_IDX == MAVLINK_PRIMARY_XML_IDX
# define MAVLINK_MESSAGE_INFO {MAVLINK_MESSAGE_INFO_STATE_INFO, MAVLINK_MESSAGE_INFO_TARGET_STATE, MAVLINK_MESSAGE_INFO_VERSION_QUERY_RESPONSE, MAVLINK_MESSAGE_INFO_LANDING_PLATFORM_HEARTBEAT, MAVLINK_MESSAGE_INFO_LANDING_PLATFORM_STATE, MAVLINK_MESSAGE_INFO_ORBIT_COMMAND, MAVLINK_MESSAGE_INFO_LEAD_FOLLOW_COMMAND, MAVLINK_MESSAGE_INFO_PLANCK_STATUS, MAVLINK_MESSAGE_INFO_PLANCK_RADIO_STATUS}
# define MAVLINK_MESSAGE_NAMES {{ "LANDING_PLATFORM_HEARTBEAT", 9235 }, { "LANDING_PLATFORM_STATE", 9236 }, { "LEAD_FOLLOW_COMMAND", 9238 }, { "ORBIT_COMMAND", 9237 }, { "PLANCK_RADIO_STATUS", 9240 }, { "PLANCK_STATUS", 9239 }, { "STATE_INFO", 9145 }, { "TARGET_STATE", 9159 }, { "VERSION_QUERY_RESPONSE", 9190 }}
# if MAVLINK_COMMAND_24BIT
#  include "../mavlink_get_info.h"
# endif
#endif

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MAVLINK_PLANCKAERO_H
