#pragma once
// MESSAGE PLANCK_START_RETURN_TO_LANDING_PLATFORM PACKING

#define MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM 9006

MAVPACKED(
typedef struct __mavlink_planck_start_return_to_landing_platform_t {
 float alt; /*< [m] Altitude at which to return*/
 float rate_up; /*< [m/s] Ascent rate during initial ascent*/
 float rate_down; /*< [m/s] Descent rate before landing*/
 uint8_t target_system; /*<  System ID*/
 uint8_t target_component; /*<  Component ID*/
}) mavlink_planck_start_return_to_landing_platform_t;

#define MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM_LEN 14
#define MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM_MIN_LEN 14
#define MAVLINK_MSG_ID_9006_LEN 14
#define MAVLINK_MSG_ID_9006_MIN_LEN 14

#define MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM_CRC 115
#define MAVLINK_MSG_ID_9006_CRC 115



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_PLANCK_START_RETURN_TO_LANDING_PLATFORM { \
    9006, \
    "PLANCK_START_RETURN_TO_LANDING_PLATFORM", \
    5, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_planck_start_return_to_landing_platform_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 13, offsetof(mavlink_planck_start_return_to_landing_platform_t, target_component) }, \
         { "alt", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_planck_start_return_to_landing_platform_t, alt) }, \
         { "rate_up", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_planck_start_return_to_landing_platform_t, rate_up) }, \
         { "rate_down", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_planck_start_return_to_landing_platform_t, rate_down) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_PLANCK_START_RETURN_TO_LANDING_PLATFORM { \
    "PLANCK_START_RETURN_TO_LANDING_PLATFORM", \
    5, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_planck_start_return_to_landing_platform_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 13, offsetof(mavlink_planck_start_return_to_landing_platform_t, target_component) }, \
         { "alt", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_planck_start_return_to_landing_platform_t, alt) }, \
         { "rate_up", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_planck_start_return_to_landing_platform_t, rate_up) }, \
         { "rate_down", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_planck_start_return_to_landing_platform_t, rate_down) }, \
         } \
}
#endif

/**
 * @brief Pack a planck_start_return_to_landing_platform message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system  System ID
 * @param target_component  Component ID
 * @param alt [m] Altitude at which to return
 * @param rate_up [m/s] Ascent rate during initial ascent
 * @param rate_down [m/s] Descent rate before landing
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_planck_start_return_to_landing_platform_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t target_system, uint8_t target_component, float alt, float rate_up, float rate_down)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM_LEN];
    _mav_put_float(buf, 0, alt);
    _mav_put_float(buf, 4, rate_up);
    _mav_put_float(buf, 8, rate_down);
    _mav_put_uint8_t(buf, 12, target_system);
    _mav_put_uint8_t(buf, 13, target_component);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM_LEN);
#else
    mavlink_planck_start_return_to_landing_platform_t packet;
    packet.alt = alt;
    packet.rate_up = rate_up;
    packet.rate_down = rate_down;
    packet.target_system = target_system;
    packet.target_component = target_component;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM_MIN_LEN, MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM_LEN, MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM_CRC);
}

/**
 * @brief Pack a planck_start_return_to_landing_platform message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system  System ID
 * @param target_component  Component ID
 * @param alt [m] Altitude at which to return
 * @param rate_up [m/s] Ascent rate during initial ascent
 * @param rate_down [m/s] Descent rate before landing
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_planck_start_return_to_landing_platform_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t target_system,uint8_t target_component,float alt,float rate_up,float rate_down)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM_LEN];
    _mav_put_float(buf, 0, alt);
    _mav_put_float(buf, 4, rate_up);
    _mav_put_float(buf, 8, rate_down);
    _mav_put_uint8_t(buf, 12, target_system);
    _mav_put_uint8_t(buf, 13, target_component);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM_LEN);
#else
    mavlink_planck_start_return_to_landing_platform_t packet;
    packet.alt = alt;
    packet.rate_up = rate_up;
    packet.rate_down = rate_down;
    packet.target_system = target_system;
    packet.target_component = target_component;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM_MIN_LEN, MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM_LEN, MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM_CRC);
}

/**
 * @brief Encode a planck_start_return_to_landing_platform struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param planck_start_return_to_landing_platform C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_planck_start_return_to_landing_platform_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_planck_start_return_to_landing_platform_t* planck_start_return_to_landing_platform)
{
    return mavlink_msg_planck_start_return_to_landing_platform_pack(system_id, component_id, msg, planck_start_return_to_landing_platform->target_system, planck_start_return_to_landing_platform->target_component, planck_start_return_to_landing_platform->alt, planck_start_return_to_landing_platform->rate_up, planck_start_return_to_landing_platform->rate_down);
}

/**
 * @brief Encode a planck_start_return_to_landing_platform struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param planck_start_return_to_landing_platform C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_planck_start_return_to_landing_platform_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_planck_start_return_to_landing_platform_t* planck_start_return_to_landing_platform)
{
    return mavlink_msg_planck_start_return_to_landing_platform_pack_chan(system_id, component_id, chan, msg, planck_start_return_to_landing_platform->target_system, planck_start_return_to_landing_platform->target_component, planck_start_return_to_landing_platform->alt, planck_start_return_to_landing_platform->rate_up, planck_start_return_to_landing_platform->rate_down);
}

/**
 * @brief Send a planck_start_return_to_landing_platform message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system  System ID
 * @param target_component  Component ID
 * @param alt [m] Altitude at which to return
 * @param rate_up [m/s] Ascent rate during initial ascent
 * @param rate_down [m/s] Descent rate before landing
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_planck_start_return_to_landing_platform_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, float alt, float rate_up, float rate_down)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM_LEN];
    _mav_put_float(buf, 0, alt);
    _mav_put_float(buf, 4, rate_up);
    _mav_put_float(buf, 8, rate_down);
    _mav_put_uint8_t(buf, 12, target_system);
    _mav_put_uint8_t(buf, 13, target_component);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM, buf, MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM_MIN_LEN, MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM_LEN, MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM_CRC);
#else
    mavlink_planck_start_return_to_landing_platform_t packet;
    packet.alt = alt;
    packet.rate_up = rate_up;
    packet.rate_down = rate_down;
    packet.target_system = target_system;
    packet.target_component = target_component;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM, (const char *)&packet, MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM_MIN_LEN, MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM_LEN, MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM_CRC);
#endif
}

/**
 * @brief Send a planck_start_return_to_landing_platform message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_planck_start_return_to_landing_platform_send_struct(mavlink_channel_t chan, const mavlink_planck_start_return_to_landing_platform_t* planck_start_return_to_landing_platform)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_planck_start_return_to_landing_platform_send(chan, planck_start_return_to_landing_platform->target_system, planck_start_return_to_landing_platform->target_component, planck_start_return_to_landing_platform->alt, planck_start_return_to_landing_platform->rate_up, planck_start_return_to_landing_platform->rate_down);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM, (const char *)planck_start_return_to_landing_platform, MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM_MIN_LEN, MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM_LEN, MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM_CRC);
#endif
}

#if MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_planck_start_return_to_landing_platform_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t target_system, uint8_t target_component, float alt, float rate_up, float rate_down)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, alt);
    _mav_put_float(buf, 4, rate_up);
    _mav_put_float(buf, 8, rate_down);
    _mav_put_uint8_t(buf, 12, target_system);
    _mav_put_uint8_t(buf, 13, target_component);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM, buf, MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM_MIN_LEN, MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM_LEN, MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM_CRC);
#else
    mavlink_planck_start_return_to_landing_platform_t *packet = (mavlink_planck_start_return_to_landing_platform_t *)msgbuf;
    packet->alt = alt;
    packet->rate_up = rate_up;
    packet->rate_down = rate_down;
    packet->target_system = target_system;
    packet->target_component = target_component;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM, (const char *)packet, MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM_MIN_LEN, MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM_LEN, MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM_CRC);
#endif
}
#endif

#endif

// MESSAGE PLANCK_START_RETURN_TO_LANDING_PLATFORM UNPACKING


/**
 * @brief Get field target_system from planck_start_return_to_landing_platform message
 *
 * @return  System ID
 */
static inline uint8_t mavlink_msg_planck_start_return_to_landing_platform_get_target_system(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  12);
}

/**
 * @brief Get field target_component from planck_start_return_to_landing_platform message
 *
 * @return  Component ID
 */
static inline uint8_t mavlink_msg_planck_start_return_to_landing_platform_get_target_component(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  13);
}

/**
 * @brief Get field alt from planck_start_return_to_landing_platform message
 *
 * @return [m] Altitude at which to return
 */
static inline float mavlink_msg_planck_start_return_to_landing_platform_get_alt(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field rate_up from planck_start_return_to_landing_platform message
 *
 * @return [m/s] Ascent rate during initial ascent
 */
static inline float mavlink_msg_planck_start_return_to_landing_platform_get_rate_up(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field rate_down from planck_start_return_to_landing_platform message
 *
 * @return [m/s] Descent rate before landing
 */
static inline float mavlink_msg_planck_start_return_to_landing_platform_get_rate_down(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Decode a planck_start_return_to_landing_platform message into a struct
 *
 * @param msg The message to decode
 * @param planck_start_return_to_landing_platform C-struct to decode the message contents into
 */
static inline void mavlink_msg_planck_start_return_to_landing_platform_decode(const mavlink_message_t* msg, mavlink_planck_start_return_to_landing_platform_t* planck_start_return_to_landing_platform)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    planck_start_return_to_landing_platform->alt = mavlink_msg_planck_start_return_to_landing_platform_get_alt(msg);
    planck_start_return_to_landing_platform->rate_up = mavlink_msg_planck_start_return_to_landing_platform_get_rate_up(msg);
    planck_start_return_to_landing_platform->rate_down = mavlink_msg_planck_start_return_to_landing_platform_get_rate_down(msg);
    planck_start_return_to_landing_platform->target_system = mavlink_msg_planck_start_return_to_landing_platform_get_target_system(msg);
    planck_start_return_to_landing_platform->target_component = mavlink_msg_planck_start_return_to_landing_platform_get_target_component(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM_LEN? msg->len : MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM_LEN;
        memset(planck_start_return_to_landing_platform, 0, MAVLINK_MSG_ID_PLANCK_START_RETURN_TO_LANDING_PLATFORM_LEN);
    memcpy(planck_start_return_to_landing_platform, _MAV_PAYLOAD(msg), len);
#endif
}
