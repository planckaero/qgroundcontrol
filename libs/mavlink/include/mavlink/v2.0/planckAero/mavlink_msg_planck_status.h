#pragma once
// MESSAGE PLANCK_STATUS PACKING

#define MAVLINK_MSG_ID_PLANCK_STATUS 9003

MAVPACKED(
typedef struct __mavlink_planck_status_t {
 uint8_t target_system; /*<  System ID*/
 uint8_t target_component; /*<  Component ID*/
 uint8_t status; /*<  Controller status bitfield (TAG_ESTIMATOR_OK=bit0, BOAT_ESTIMATOR_OK=bit1)*/
 uint8_t failsafe; /*<  Failsafe status bitfield (COMMBOX_OK=bit0, COMMBOX_GPS_OK)*/
 uint8_t takeoff_ready; /*<  Ready for takeoff*/
 uint8_t land_ready; /*<  Ready for landing*/
 uint8_t takeoff_complete; /*<  Takeoff has completed (reached target altitude)*/
 uint8_t at_location; /*<  Copter has reached target location*/
}) mavlink_planck_status_t;

#define MAVLINK_MSG_ID_PLANCK_STATUS_LEN 8
#define MAVLINK_MSG_ID_PLANCK_STATUS_MIN_LEN 8
#define MAVLINK_MSG_ID_9003_LEN 8
#define MAVLINK_MSG_ID_9003_MIN_LEN 8

#define MAVLINK_MSG_ID_PLANCK_STATUS_CRC 252
#define MAVLINK_MSG_ID_9003_CRC 252



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_PLANCK_STATUS { \
    9003, \
    "PLANCK_STATUS", \
    8, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_planck_status_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_planck_status_t, target_component) }, \
         { "status", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_planck_status_t, status) }, \
         { "failsafe", NULL, MAVLINK_TYPE_UINT8_T, 0, 3, offsetof(mavlink_planck_status_t, failsafe) }, \
         { "takeoff_ready", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_planck_status_t, takeoff_ready) }, \
         { "land_ready", NULL, MAVLINK_TYPE_UINT8_T, 0, 5, offsetof(mavlink_planck_status_t, land_ready) }, \
         { "takeoff_complete", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_planck_status_t, takeoff_complete) }, \
         { "at_location", NULL, MAVLINK_TYPE_UINT8_T, 0, 7, offsetof(mavlink_planck_status_t, at_location) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_PLANCK_STATUS { \
    "PLANCK_STATUS", \
    8, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_planck_status_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_planck_status_t, target_component) }, \
         { "status", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_planck_status_t, status) }, \
         { "failsafe", NULL, MAVLINK_TYPE_UINT8_T, 0, 3, offsetof(mavlink_planck_status_t, failsafe) }, \
         { "takeoff_ready", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_planck_status_t, takeoff_ready) }, \
         { "land_ready", NULL, MAVLINK_TYPE_UINT8_T, 0, 5, offsetof(mavlink_planck_status_t, land_ready) }, \
         { "takeoff_complete", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_planck_status_t, takeoff_complete) }, \
         { "at_location", NULL, MAVLINK_TYPE_UINT8_T, 0, 7, offsetof(mavlink_planck_status_t, at_location) }, \
         } \
}
#endif

/**
 * @brief Pack a planck_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system  System ID
 * @param target_component  Component ID
 * @param status  Controller status bitfield (TAG_ESTIMATOR_OK=bit0, BOAT_ESTIMATOR_OK=bit1)
 * @param failsafe  Failsafe status bitfield (COMMBOX_OK=bit0, COMMBOX_GPS_OK)
 * @param takeoff_ready  Ready for takeoff
 * @param land_ready  Ready for landing
 * @param takeoff_complete  Takeoff has completed (reached target altitude)
 * @param at_location  Copter has reached target location
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_planck_status_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t target_system, uint8_t target_component, uint8_t status, uint8_t failsafe, uint8_t takeoff_ready, uint8_t land_ready, uint8_t takeoff_complete, uint8_t at_location)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLANCK_STATUS_LEN];
    _mav_put_uint8_t(buf, 0, target_system);
    _mav_put_uint8_t(buf, 1, target_component);
    _mav_put_uint8_t(buf, 2, status);
    _mav_put_uint8_t(buf, 3, failsafe);
    _mav_put_uint8_t(buf, 4, takeoff_ready);
    _mav_put_uint8_t(buf, 5, land_ready);
    _mav_put_uint8_t(buf, 6, takeoff_complete);
    _mav_put_uint8_t(buf, 7, at_location);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PLANCK_STATUS_LEN);
#else
    mavlink_planck_status_t packet;
    packet.target_system = target_system;
    packet.target_component = target_component;
    packet.status = status;
    packet.failsafe = failsafe;
    packet.takeoff_ready = takeoff_ready;
    packet.land_ready = land_ready;
    packet.takeoff_complete = takeoff_complete;
    packet.at_location = at_location;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PLANCK_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PLANCK_STATUS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_PLANCK_STATUS_MIN_LEN, MAVLINK_MSG_ID_PLANCK_STATUS_LEN, MAVLINK_MSG_ID_PLANCK_STATUS_CRC);
}

/**
 * @brief Pack a planck_status message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system  System ID
 * @param target_component  Component ID
 * @param status  Controller status bitfield (TAG_ESTIMATOR_OK=bit0, BOAT_ESTIMATOR_OK=bit1)
 * @param failsafe  Failsafe status bitfield (COMMBOX_OK=bit0, COMMBOX_GPS_OK)
 * @param takeoff_ready  Ready for takeoff
 * @param land_ready  Ready for landing
 * @param takeoff_complete  Takeoff has completed (reached target altitude)
 * @param at_location  Copter has reached target location
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_planck_status_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t target_system,uint8_t target_component,uint8_t status,uint8_t failsafe,uint8_t takeoff_ready,uint8_t land_ready,uint8_t takeoff_complete,uint8_t at_location)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLANCK_STATUS_LEN];
    _mav_put_uint8_t(buf, 0, target_system);
    _mav_put_uint8_t(buf, 1, target_component);
    _mav_put_uint8_t(buf, 2, status);
    _mav_put_uint8_t(buf, 3, failsafe);
    _mav_put_uint8_t(buf, 4, takeoff_ready);
    _mav_put_uint8_t(buf, 5, land_ready);
    _mav_put_uint8_t(buf, 6, takeoff_complete);
    _mav_put_uint8_t(buf, 7, at_location);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PLANCK_STATUS_LEN);
#else
    mavlink_planck_status_t packet;
    packet.target_system = target_system;
    packet.target_component = target_component;
    packet.status = status;
    packet.failsafe = failsafe;
    packet.takeoff_ready = takeoff_ready;
    packet.land_ready = land_ready;
    packet.takeoff_complete = takeoff_complete;
    packet.at_location = at_location;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PLANCK_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PLANCK_STATUS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_PLANCK_STATUS_MIN_LEN, MAVLINK_MSG_ID_PLANCK_STATUS_LEN, MAVLINK_MSG_ID_PLANCK_STATUS_CRC);
}

/**
 * @brief Encode a planck_status struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param planck_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_planck_status_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_planck_status_t* planck_status)
{
    return mavlink_msg_planck_status_pack(system_id, component_id, msg, planck_status->target_system, planck_status->target_component, planck_status->status, planck_status->failsafe, planck_status->takeoff_ready, planck_status->land_ready, planck_status->takeoff_complete, planck_status->at_location);
}

/**
 * @brief Encode a planck_status struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param planck_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_planck_status_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_planck_status_t* planck_status)
{
    return mavlink_msg_planck_status_pack_chan(system_id, component_id, chan, msg, planck_status->target_system, planck_status->target_component, planck_status->status, planck_status->failsafe, planck_status->takeoff_ready, planck_status->land_ready, planck_status->takeoff_complete, planck_status->at_location);
}

/**
 * @brief Send a planck_status message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system  System ID
 * @param target_component  Component ID
 * @param status  Controller status bitfield (TAG_ESTIMATOR_OK=bit0, BOAT_ESTIMATOR_OK=bit1)
 * @param failsafe  Failsafe status bitfield (COMMBOX_OK=bit0, COMMBOX_GPS_OK)
 * @param takeoff_ready  Ready for takeoff
 * @param land_ready  Ready for landing
 * @param takeoff_complete  Takeoff has completed (reached target altitude)
 * @param at_location  Copter has reached target location
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_planck_status_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, uint8_t status, uint8_t failsafe, uint8_t takeoff_ready, uint8_t land_ready, uint8_t takeoff_complete, uint8_t at_location)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLANCK_STATUS_LEN];
    _mav_put_uint8_t(buf, 0, target_system);
    _mav_put_uint8_t(buf, 1, target_component);
    _mav_put_uint8_t(buf, 2, status);
    _mav_put_uint8_t(buf, 3, failsafe);
    _mav_put_uint8_t(buf, 4, takeoff_ready);
    _mav_put_uint8_t(buf, 5, land_ready);
    _mav_put_uint8_t(buf, 6, takeoff_complete);
    _mav_put_uint8_t(buf, 7, at_location);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_STATUS, buf, MAVLINK_MSG_ID_PLANCK_STATUS_MIN_LEN, MAVLINK_MSG_ID_PLANCK_STATUS_LEN, MAVLINK_MSG_ID_PLANCK_STATUS_CRC);
#else
    mavlink_planck_status_t packet;
    packet.target_system = target_system;
    packet.target_component = target_component;
    packet.status = status;
    packet.failsafe = failsafe;
    packet.takeoff_ready = takeoff_ready;
    packet.land_ready = land_ready;
    packet.takeoff_complete = takeoff_complete;
    packet.at_location = at_location;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_STATUS, (const char *)&packet, MAVLINK_MSG_ID_PLANCK_STATUS_MIN_LEN, MAVLINK_MSG_ID_PLANCK_STATUS_LEN, MAVLINK_MSG_ID_PLANCK_STATUS_CRC);
#endif
}

/**
 * @brief Send a planck_status message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_planck_status_send_struct(mavlink_channel_t chan, const mavlink_planck_status_t* planck_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_planck_status_send(chan, planck_status->target_system, planck_status->target_component, planck_status->status, planck_status->failsafe, planck_status->takeoff_ready, planck_status->land_ready, planck_status->takeoff_complete, planck_status->at_location);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_STATUS, (const char *)planck_status, MAVLINK_MSG_ID_PLANCK_STATUS_MIN_LEN, MAVLINK_MSG_ID_PLANCK_STATUS_LEN, MAVLINK_MSG_ID_PLANCK_STATUS_CRC);
#endif
}

#if MAVLINK_MSG_ID_PLANCK_STATUS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_planck_status_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t target_system, uint8_t target_component, uint8_t status, uint8_t failsafe, uint8_t takeoff_ready, uint8_t land_ready, uint8_t takeoff_complete, uint8_t at_location)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, target_system);
    _mav_put_uint8_t(buf, 1, target_component);
    _mav_put_uint8_t(buf, 2, status);
    _mav_put_uint8_t(buf, 3, failsafe);
    _mav_put_uint8_t(buf, 4, takeoff_ready);
    _mav_put_uint8_t(buf, 5, land_ready);
    _mav_put_uint8_t(buf, 6, takeoff_complete);
    _mav_put_uint8_t(buf, 7, at_location);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_STATUS, buf, MAVLINK_MSG_ID_PLANCK_STATUS_MIN_LEN, MAVLINK_MSG_ID_PLANCK_STATUS_LEN, MAVLINK_MSG_ID_PLANCK_STATUS_CRC);
#else
    mavlink_planck_status_t *packet = (mavlink_planck_status_t *)msgbuf;
    packet->target_system = target_system;
    packet->target_component = target_component;
    packet->status = status;
    packet->failsafe = failsafe;
    packet->takeoff_ready = takeoff_ready;
    packet->land_ready = land_ready;
    packet->takeoff_complete = takeoff_complete;
    packet->at_location = at_location;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_STATUS, (const char *)packet, MAVLINK_MSG_ID_PLANCK_STATUS_MIN_LEN, MAVLINK_MSG_ID_PLANCK_STATUS_LEN, MAVLINK_MSG_ID_PLANCK_STATUS_CRC);
#endif
}
#endif

#endif

// MESSAGE PLANCK_STATUS UNPACKING


/**
 * @brief Get field target_system from planck_status message
 *
 * @return  System ID
 */
static inline uint8_t mavlink_msg_planck_status_get_target_system(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field target_component from planck_status message
 *
 * @return  Component ID
 */
static inline uint8_t mavlink_msg_planck_status_get_target_component(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Get field status from planck_status message
 *
 * @return  Controller status bitfield (TAG_ESTIMATOR_OK=bit0, BOAT_ESTIMATOR_OK=bit1)
 */
static inline uint8_t mavlink_msg_planck_status_get_status(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  2);
}

/**
 * @brief Get field failsafe from planck_status message
 *
 * @return  Failsafe status bitfield (COMMBOX_OK=bit0, COMMBOX_GPS_OK)
 */
static inline uint8_t mavlink_msg_planck_status_get_failsafe(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  3);
}

/**
 * @brief Get field takeoff_ready from planck_status message
 *
 * @return  Ready for takeoff
 */
static inline uint8_t mavlink_msg_planck_status_get_takeoff_ready(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  4);
}

/**
 * @brief Get field land_ready from planck_status message
 *
 * @return  Ready for landing
 */
static inline uint8_t mavlink_msg_planck_status_get_land_ready(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  5);
}

/**
 * @brief Get field takeoff_complete from planck_status message
 *
 * @return  Takeoff has completed (reached target altitude)
 */
static inline uint8_t mavlink_msg_planck_status_get_takeoff_complete(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  6);
}

/**
 * @brief Get field at_location from planck_status message
 *
 * @return  Copter has reached target location
 */
static inline uint8_t mavlink_msg_planck_status_get_at_location(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  7);
}

/**
 * @brief Decode a planck_status message into a struct
 *
 * @param msg The message to decode
 * @param planck_status C-struct to decode the message contents into
 */
static inline void mavlink_msg_planck_status_decode(const mavlink_message_t* msg, mavlink_planck_status_t* planck_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    planck_status->target_system = mavlink_msg_planck_status_get_target_system(msg);
    planck_status->target_component = mavlink_msg_planck_status_get_target_component(msg);
    planck_status->status = mavlink_msg_planck_status_get_status(msg);
    planck_status->failsafe = mavlink_msg_planck_status_get_failsafe(msg);
    planck_status->takeoff_ready = mavlink_msg_planck_status_get_takeoff_ready(msg);
    planck_status->land_ready = mavlink_msg_planck_status_get_land_ready(msg);
    planck_status->takeoff_complete = mavlink_msg_planck_status_get_takeoff_complete(msg);
    planck_status->at_location = mavlink_msg_planck_status_get_at_location(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_PLANCK_STATUS_LEN? msg->len : MAVLINK_MSG_ID_PLANCK_STATUS_LEN;
        memset(planck_status, 0, MAVLINK_MSG_ID_PLANCK_STATUS_LEN);
    memcpy(planck_status, _MAV_PAYLOAD(msg), len);
#endif
}
