#pragma once
// MESSAGE PLANCK_STATUS PACKING

#define MAVLINK_MSG_ID_PLANCK_STATUS 239

MAVPACKED(
typedef struct __mavlink_planck_status_t {
 uint8_t mode; /*< Vehicle state (IDLE=0, TAKEOFF, STAB, RTB, SEARCHING, LAND_READY, LAND, ORBIT, LEAD_FOLLOW)*/
 uint8_t status; /*< Controller status bitfield (TAG_ESTIMATOR_OK=bit0, BOAT_ESTIMATOR_OK=bit1)*/
 uint8_t failsafe; /*< Failsafe status bitfield (RC_OK=bit0, COMMBOX_OK=bit1, BATTERY_OK=bit2, COMMBOX_GPS_OK)*/
}) mavlink_planck_status_t;

#define MAVLINK_MSG_ID_PLANCK_STATUS_LEN 3
#define MAVLINK_MSG_ID_PLANCK_STATUS_MIN_LEN 3
#define MAVLINK_MSG_ID_239_LEN 3
#define MAVLINK_MSG_ID_239_MIN_LEN 3

#define MAVLINK_MSG_ID_PLANCK_STATUS_CRC 211
#define MAVLINK_MSG_ID_239_CRC 211



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_PLANCK_STATUS { \
    239, \
    "PLANCK_STATUS", \
    3, \
    {  { "mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_planck_status_t, mode) }, \
         { "status", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_planck_status_t, status) }, \
         { "failsafe", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_planck_status_t, failsafe) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_PLANCK_STATUS { \
    "PLANCK_STATUS", \
    3, \
    {  { "mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_planck_status_t, mode) }, \
         { "status", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_planck_status_t, status) }, \
         { "failsafe", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_planck_status_t, failsafe) }, \
         } \
}
#endif

/**
 * @brief Pack a planck_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param mode Vehicle state (IDLE=0, TAKEOFF, STAB, RTB, SEARCHING, LAND_READY, LAND, ORBIT, LEAD_FOLLOW)
 * @param status Controller status bitfield (TAG_ESTIMATOR_OK=bit0, BOAT_ESTIMATOR_OK=bit1)
 * @param failsafe Failsafe status bitfield (RC_OK=bit0, COMMBOX_OK=bit1, BATTERY_OK=bit2, COMMBOX_GPS_OK)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_planck_status_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t mode, uint8_t status, uint8_t failsafe)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLANCK_STATUS_LEN];
    _mav_put_uint8_t(buf, 0, mode);
    _mav_put_uint8_t(buf, 1, status);
    _mav_put_uint8_t(buf, 2, failsafe);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PLANCK_STATUS_LEN);
#else
    mavlink_planck_status_t packet;
    packet.mode = mode;
    packet.status = status;
    packet.failsafe = failsafe;

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
 * @param mode Vehicle state (IDLE=0, TAKEOFF, STAB, RTB, SEARCHING, LAND_READY, LAND, ORBIT, LEAD_FOLLOW)
 * @param status Controller status bitfield (TAG_ESTIMATOR_OK=bit0, BOAT_ESTIMATOR_OK=bit1)
 * @param failsafe Failsafe status bitfield (RC_OK=bit0, COMMBOX_OK=bit1, BATTERY_OK=bit2, COMMBOX_GPS_OK)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_planck_status_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t mode,uint8_t status,uint8_t failsafe)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLANCK_STATUS_LEN];
    _mav_put_uint8_t(buf, 0, mode);
    _mav_put_uint8_t(buf, 1, status);
    _mav_put_uint8_t(buf, 2, failsafe);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PLANCK_STATUS_LEN);
#else
    mavlink_planck_status_t packet;
    packet.mode = mode;
    packet.status = status;
    packet.failsafe = failsafe;

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
    return mavlink_msg_planck_status_pack(system_id, component_id, msg, planck_status->mode, planck_status->status, planck_status->failsafe);
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
    return mavlink_msg_planck_status_pack_chan(system_id, component_id, chan, msg, planck_status->mode, planck_status->status, planck_status->failsafe);
}

/**
 * @brief Send a planck_status message
 * @param chan MAVLink channel to send the message
 *
 * @param mode Vehicle state (IDLE=0, TAKEOFF, STAB, RTB, SEARCHING, LAND_READY, LAND, ORBIT, LEAD_FOLLOW)
 * @param status Controller status bitfield (TAG_ESTIMATOR_OK=bit0, BOAT_ESTIMATOR_OK=bit1)
 * @param failsafe Failsafe status bitfield (RC_OK=bit0, COMMBOX_OK=bit1, BATTERY_OK=bit2, COMMBOX_GPS_OK)
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_planck_status_send(mavlink_channel_t chan, uint8_t mode, uint8_t status, uint8_t failsafe)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLANCK_STATUS_LEN];
    _mav_put_uint8_t(buf, 0, mode);
    _mav_put_uint8_t(buf, 1, status);
    _mav_put_uint8_t(buf, 2, failsafe);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_STATUS, buf, MAVLINK_MSG_ID_PLANCK_STATUS_MIN_LEN, MAVLINK_MSG_ID_PLANCK_STATUS_LEN, MAVLINK_MSG_ID_PLANCK_STATUS_CRC);
#else
    mavlink_planck_status_t packet;
    packet.mode = mode;
    packet.status = status;
    packet.failsafe = failsafe;

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
    mavlink_msg_planck_status_send(chan, planck_status->mode, planck_status->status, planck_status->failsafe);
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
static inline void mavlink_msg_planck_status_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t mode, uint8_t status, uint8_t failsafe)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, mode);
    _mav_put_uint8_t(buf, 1, status);
    _mav_put_uint8_t(buf, 2, failsafe);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_STATUS, buf, MAVLINK_MSG_ID_PLANCK_STATUS_MIN_LEN, MAVLINK_MSG_ID_PLANCK_STATUS_LEN, MAVLINK_MSG_ID_PLANCK_STATUS_CRC);
#else
    mavlink_planck_status_t *packet = (mavlink_planck_status_t *)msgbuf;
    packet->mode = mode;
    packet->status = status;
    packet->failsafe = failsafe;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_STATUS, (const char *)packet, MAVLINK_MSG_ID_PLANCK_STATUS_MIN_LEN, MAVLINK_MSG_ID_PLANCK_STATUS_LEN, MAVLINK_MSG_ID_PLANCK_STATUS_CRC);
#endif
}
#endif

#endif

// MESSAGE PLANCK_STATUS UNPACKING


/**
 * @brief Get field mode from planck_status message
 *
 * @return Vehicle state (IDLE=0, TAKEOFF, STAB, RTB, SEARCHING, LAND_READY, LAND, ORBIT, LEAD_FOLLOW)
 */
static inline uint8_t mavlink_msg_planck_status_get_mode(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field status from planck_status message
 *
 * @return Controller status bitfield (TAG_ESTIMATOR_OK=bit0, BOAT_ESTIMATOR_OK=bit1)
 */
static inline uint8_t mavlink_msg_planck_status_get_status(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Get field failsafe from planck_status message
 *
 * @return Failsafe status bitfield (RC_OK=bit0, COMMBOX_OK=bit1, BATTERY_OK=bit2, COMMBOX_GPS_OK)
 */
static inline uint8_t mavlink_msg_planck_status_get_failsafe(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  2);
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
    planck_status->mode = mavlink_msg_planck_status_get_mode(msg);
    planck_status->status = mavlink_msg_planck_status_get_status(msg);
    planck_status->failsafe = mavlink_msg_planck_status_get_failsafe(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_PLANCK_STATUS_LEN? msg->len : MAVLINK_MSG_ID_PLANCK_STATUS_LEN;
        memset(planck_status, 0, MAVLINK_MSG_ID_PLANCK_STATUS_LEN);
    memcpy(planck_status, _MAV_PAYLOAD(msg), len);
#endif
}
