#pragma once
// MESSAGE PLANCK_STOP_CONTROLLING PACKING

#define MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING 9008

MAVPACKED(
typedef struct __mavlink_planck_stop_controlling_t {
 uint8_t target_system; /*<  System which should execute the command*/
 uint8_t target_component; /*<  Component which should execute the command, 0 for all components*/
 uint8_t stop; /*<  1: stop controlling, 0: keep controlling*/
}) mavlink_planck_stop_controlling_t;

#define MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING_LEN 3
#define MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING_MIN_LEN 3
#define MAVLINK_MSG_ID_9008_LEN 3
#define MAVLINK_MSG_ID_9008_MIN_LEN 3

#define MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING_CRC 43
#define MAVLINK_MSG_ID_9008_CRC 43



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_PLANCK_STOP_CONTROLLING { \
    9008, \
    "PLANCK_STOP_CONTROLLING", \
    3, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_planck_stop_controlling_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_planck_stop_controlling_t, target_component) }, \
         { "stop", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_planck_stop_controlling_t, stop) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_PLANCK_STOP_CONTROLLING { \
    "PLANCK_STOP_CONTROLLING", \
    3, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_planck_stop_controlling_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_planck_stop_controlling_t, target_component) }, \
         { "stop", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_planck_stop_controlling_t, stop) }, \
         } \
}
#endif

/**
 * @brief Pack a planck_stop_controlling message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system  System which should execute the command
 * @param target_component  Component which should execute the command, 0 for all components
 * @param stop  1: stop controlling, 0: keep controlling
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_planck_stop_controlling_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t target_system, uint8_t target_component, uint8_t stop)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING_LEN];
    _mav_put_uint8_t(buf, 0, target_system);
    _mav_put_uint8_t(buf, 1, target_component);
    _mav_put_uint8_t(buf, 2, stop);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING_LEN);
#else
    mavlink_planck_stop_controlling_t packet;
    packet.target_system = target_system;
    packet.target_component = target_component;
    packet.stop = stop;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING_MIN_LEN, MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING_LEN, MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING_CRC);
}

/**
 * @brief Pack a planck_stop_controlling message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system  System which should execute the command
 * @param target_component  Component which should execute the command, 0 for all components
 * @param stop  1: stop controlling, 0: keep controlling
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_planck_stop_controlling_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t target_system,uint8_t target_component,uint8_t stop)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING_LEN];
    _mav_put_uint8_t(buf, 0, target_system);
    _mav_put_uint8_t(buf, 1, target_component);
    _mav_put_uint8_t(buf, 2, stop);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING_LEN);
#else
    mavlink_planck_stop_controlling_t packet;
    packet.target_system = target_system;
    packet.target_component = target_component;
    packet.stop = stop;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING_MIN_LEN, MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING_LEN, MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING_CRC);
}

/**
 * @brief Encode a planck_stop_controlling struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param planck_stop_controlling C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_planck_stop_controlling_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_planck_stop_controlling_t* planck_stop_controlling)
{
    return mavlink_msg_planck_stop_controlling_pack(system_id, component_id, msg, planck_stop_controlling->target_system, planck_stop_controlling->target_component, planck_stop_controlling->stop);
}

/**
 * @brief Encode a planck_stop_controlling struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param planck_stop_controlling C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_planck_stop_controlling_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_planck_stop_controlling_t* planck_stop_controlling)
{
    return mavlink_msg_planck_stop_controlling_pack_chan(system_id, component_id, chan, msg, planck_stop_controlling->target_system, planck_stop_controlling->target_component, planck_stop_controlling->stop);
}

/**
 * @brief Send a planck_stop_controlling message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system  System which should execute the command
 * @param target_component  Component which should execute the command, 0 for all components
 * @param stop  1: stop controlling, 0: keep controlling
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_planck_stop_controlling_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, uint8_t stop)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING_LEN];
    _mav_put_uint8_t(buf, 0, target_system);
    _mav_put_uint8_t(buf, 1, target_component);
    _mav_put_uint8_t(buf, 2, stop);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING, buf, MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING_MIN_LEN, MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING_LEN, MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING_CRC);
#else
    mavlink_planck_stop_controlling_t packet;
    packet.target_system = target_system;
    packet.target_component = target_component;
    packet.stop = stop;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING, (const char *)&packet, MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING_MIN_LEN, MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING_LEN, MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING_CRC);
#endif
}

/**
 * @brief Send a planck_stop_controlling message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_planck_stop_controlling_send_struct(mavlink_channel_t chan, const mavlink_planck_stop_controlling_t* planck_stop_controlling)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_planck_stop_controlling_send(chan, planck_stop_controlling->target_system, planck_stop_controlling->target_component, planck_stop_controlling->stop);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING, (const char *)planck_stop_controlling, MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING_MIN_LEN, MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING_LEN, MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING_CRC);
#endif
}

#if MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_planck_stop_controlling_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t target_system, uint8_t target_component, uint8_t stop)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, target_system);
    _mav_put_uint8_t(buf, 1, target_component);
    _mav_put_uint8_t(buf, 2, stop);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING, buf, MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING_MIN_LEN, MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING_LEN, MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING_CRC);
#else
    mavlink_planck_stop_controlling_t *packet = (mavlink_planck_stop_controlling_t *)msgbuf;
    packet->target_system = target_system;
    packet->target_component = target_component;
    packet->stop = stop;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING, (const char *)packet, MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING_MIN_LEN, MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING_LEN, MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING_CRC);
#endif
}
#endif

#endif

// MESSAGE PLANCK_STOP_CONTROLLING UNPACKING


/**
 * @brief Get field target_system from planck_stop_controlling message
 *
 * @return  System which should execute the command
 */
static inline uint8_t mavlink_msg_planck_stop_controlling_get_target_system(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field target_component from planck_stop_controlling message
 *
 * @return  Component which should execute the command, 0 for all components
 */
static inline uint8_t mavlink_msg_planck_stop_controlling_get_target_component(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Get field stop from planck_stop_controlling message
 *
 * @return  1: stop controlling, 0: keep controlling
 */
static inline uint8_t mavlink_msg_planck_stop_controlling_get_stop(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  2);
}

/**
 * @brief Decode a planck_stop_controlling message into a struct
 *
 * @param msg The message to decode
 * @param planck_stop_controlling C-struct to decode the message contents into
 */
static inline void mavlink_msg_planck_stop_controlling_decode(const mavlink_message_t* msg, mavlink_planck_stop_controlling_t* planck_stop_controlling)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    planck_stop_controlling->target_system = mavlink_msg_planck_stop_controlling_get_target_system(msg);
    planck_stop_controlling->target_component = mavlink_msg_planck_stop_controlling_get_target_component(msg);
    planck_stop_controlling->stop = mavlink_msg_planck_stop_controlling_get_stop(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING_LEN? msg->len : MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING_LEN;
        memset(planck_stop_controlling, 0, MAVLINK_MSG_ID_PLANCK_STOP_CONTROLLING_LEN);
    memcpy(planck_stop_controlling, _MAV_PAYLOAD(msg), len);
#endif
}
