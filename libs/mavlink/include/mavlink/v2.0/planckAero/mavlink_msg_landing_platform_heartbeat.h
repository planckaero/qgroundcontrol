#pragma once
// MESSAGE LANDING_PLATFORM_HEARTBEAT PACKING

#define MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT 235

MAVPACKED(
typedef struct __mavlink_landing_platform_heartbeat_t {
 uint64_t time_us; /*< Wall-clock time in u-seconds of the landing platform*/
}) mavlink_landing_platform_heartbeat_t;

#define MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT_LEN 8
#define MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT_MIN_LEN 8
#define MAVLINK_MSG_ID_235_LEN 8
#define MAVLINK_MSG_ID_235_MIN_LEN 8

#define MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT_CRC 82
#define MAVLINK_MSG_ID_235_CRC 82



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_LANDING_PLATFORM_HEARTBEAT { \
    235, \
    "LANDING_PLATFORM_HEARTBEAT", \
    1, \
    {  { "time_us", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_landing_platform_heartbeat_t, time_us) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_LANDING_PLATFORM_HEARTBEAT { \
    "LANDING_PLATFORM_HEARTBEAT", \
    1, \
    {  { "time_us", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_landing_platform_heartbeat_t, time_us) }, \
         } \
}
#endif

/**
 * @brief Pack a landing_platform_heartbeat message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_us Wall-clock time in u-seconds of the landing platform
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_landing_platform_heartbeat_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t time_us)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT_LEN];
    _mav_put_uint64_t(buf, 0, time_us);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT_LEN);
#else
    mavlink_landing_platform_heartbeat_t packet;
    packet.time_us = time_us;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT_MIN_LEN, MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT_LEN, MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT_CRC);
}

/**
 * @brief Pack a landing_platform_heartbeat message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_us Wall-clock time in u-seconds of the landing platform
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_landing_platform_heartbeat_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t time_us)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT_LEN];
    _mav_put_uint64_t(buf, 0, time_us);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT_LEN);
#else
    mavlink_landing_platform_heartbeat_t packet;
    packet.time_us = time_us;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT_MIN_LEN, MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT_LEN, MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT_CRC);
}

/**
 * @brief Encode a landing_platform_heartbeat struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param landing_platform_heartbeat C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_landing_platform_heartbeat_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_landing_platform_heartbeat_t* landing_platform_heartbeat)
{
    return mavlink_msg_landing_platform_heartbeat_pack(system_id, component_id, msg, landing_platform_heartbeat->time_us);
}

/**
 * @brief Encode a landing_platform_heartbeat struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param landing_platform_heartbeat C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_landing_platform_heartbeat_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_landing_platform_heartbeat_t* landing_platform_heartbeat)
{
    return mavlink_msg_landing_platform_heartbeat_pack_chan(system_id, component_id, chan, msg, landing_platform_heartbeat->time_us);
}

/**
 * @brief Send a landing_platform_heartbeat message
 * @param chan MAVLink channel to send the message
 *
 * @param time_us Wall-clock time in u-seconds of the landing platform
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_landing_platform_heartbeat_send(mavlink_channel_t chan, uint64_t time_us)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT_LEN];
    _mav_put_uint64_t(buf, 0, time_us);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT, buf, MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT_MIN_LEN, MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT_LEN, MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT_CRC);
#else
    mavlink_landing_platform_heartbeat_t packet;
    packet.time_us = time_us;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT, (const char *)&packet, MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT_MIN_LEN, MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT_LEN, MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT_CRC);
#endif
}

/**
 * @brief Send a landing_platform_heartbeat message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_landing_platform_heartbeat_send_struct(mavlink_channel_t chan, const mavlink_landing_platform_heartbeat_t* landing_platform_heartbeat)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_landing_platform_heartbeat_send(chan, landing_platform_heartbeat->time_us);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT, (const char *)landing_platform_heartbeat, MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT_MIN_LEN, MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT_LEN, MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT_CRC);
#endif
}

#if MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_landing_platform_heartbeat_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t time_us)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, time_us);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT, buf, MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT_MIN_LEN, MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT_LEN, MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT_CRC);
#else
    mavlink_landing_platform_heartbeat_t *packet = (mavlink_landing_platform_heartbeat_t *)msgbuf;
    packet->time_us = time_us;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT, (const char *)packet, MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT_MIN_LEN, MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT_LEN, MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT_CRC);
#endif
}
#endif

#endif

// MESSAGE LANDING_PLATFORM_HEARTBEAT UNPACKING


/**
 * @brief Get field time_us from landing_platform_heartbeat message
 *
 * @return Wall-clock time in u-seconds of the landing platform
 */
static inline uint64_t mavlink_msg_landing_platform_heartbeat_get_time_us(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Decode a landing_platform_heartbeat message into a struct
 *
 * @param msg The message to decode
 * @param landing_platform_heartbeat C-struct to decode the message contents into
 */
static inline void mavlink_msg_landing_platform_heartbeat_decode(const mavlink_message_t* msg, mavlink_landing_platform_heartbeat_t* landing_platform_heartbeat)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    landing_platform_heartbeat->time_us = mavlink_msg_landing_platform_heartbeat_get_time_us(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT_LEN? msg->len : MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT_LEN;
        memset(landing_platform_heartbeat, 0, MAVLINK_MSG_ID_LANDING_PLATFORM_HEARTBEAT_LEN);
    memcpy(landing_platform_heartbeat, _MAV_PAYLOAD(msg), len);
#endif
}
