#pragma once
// MESSAGE PLANCK_START_LAND PACKING

#define MAVLINK_MSG_ID_PLANCK_START_LAND 9007

MAVPACKED(
typedef struct __mavlink_planck_start_land_t {
 float rate; /*< [m/s] Descent rate to use during landing*/
 uint8_t target_system; /*<  System ID*/
 uint8_t target_component; /*<  Component ID*/
}) mavlink_planck_start_land_t;

#define MAVLINK_MSG_ID_PLANCK_START_LAND_LEN 6
#define MAVLINK_MSG_ID_PLANCK_START_LAND_MIN_LEN 6
#define MAVLINK_MSG_ID_9007_LEN 6
#define MAVLINK_MSG_ID_9007_MIN_LEN 6

#define MAVLINK_MSG_ID_PLANCK_START_LAND_CRC 208
#define MAVLINK_MSG_ID_9007_CRC 208



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_PLANCK_START_LAND { \
    9007, \
    "PLANCK_START_LAND", \
    3, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_planck_start_land_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 5, offsetof(mavlink_planck_start_land_t, target_component) }, \
         { "rate", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_planck_start_land_t, rate) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_PLANCK_START_LAND { \
    "PLANCK_START_LAND", \
    3, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_planck_start_land_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 5, offsetof(mavlink_planck_start_land_t, target_component) }, \
         { "rate", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_planck_start_land_t, rate) }, \
         } \
}
#endif

/**
 * @brief Pack a planck_start_land message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system  System ID
 * @param target_component  Component ID
 * @param rate [m/s] Descent rate to use during landing
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_planck_start_land_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t target_system, uint8_t target_component, float rate)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLANCK_START_LAND_LEN];
    _mav_put_float(buf, 0, rate);
    _mav_put_uint8_t(buf, 4, target_system);
    _mav_put_uint8_t(buf, 5, target_component);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PLANCK_START_LAND_LEN);
#else
    mavlink_planck_start_land_t packet;
    packet.rate = rate;
    packet.target_system = target_system;
    packet.target_component = target_component;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PLANCK_START_LAND_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PLANCK_START_LAND;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_PLANCK_START_LAND_MIN_LEN, MAVLINK_MSG_ID_PLANCK_START_LAND_LEN, MAVLINK_MSG_ID_PLANCK_START_LAND_CRC);
}

/**
 * @brief Pack a planck_start_land message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system  System ID
 * @param target_component  Component ID
 * @param rate [m/s] Descent rate to use during landing
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_planck_start_land_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t target_system,uint8_t target_component,float rate)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLANCK_START_LAND_LEN];
    _mav_put_float(buf, 0, rate);
    _mav_put_uint8_t(buf, 4, target_system);
    _mav_put_uint8_t(buf, 5, target_component);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PLANCK_START_LAND_LEN);
#else
    mavlink_planck_start_land_t packet;
    packet.rate = rate;
    packet.target_system = target_system;
    packet.target_component = target_component;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PLANCK_START_LAND_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PLANCK_START_LAND;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_PLANCK_START_LAND_MIN_LEN, MAVLINK_MSG_ID_PLANCK_START_LAND_LEN, MAVLINK_MSG_ID_PLANCK_START_LAND_CRC);
}

/**
 * @brief Encode a planck_start_land struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param planck_start_land C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_planck_start_land_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_planck_start_land_t* planck_start_land)
{
    return mavlink_msg_planck_start_land_pack(system_id, component_id, msg, planck_start_land->target_system, planck_start_land->target_component, planck_start_land->rate);
}

/**
 * @brief Encode a planck_start_land struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param planck_start_land C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_planck_start_land_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_planck_start_land_t* planck_start_land)
{
    return mavlink_msg_planck_start_land_pack_chan(system_id, component_id, chan, msg, planck_start_land->target_system, planck_start_land->target_component, planck_start_land->rate);
}

/**
 * @brief Send a planck_start_land message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system  System ID
 * @param target_component  Component ID
 * @param rate [m/s] Descent rate to use during landing
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_planck_start_land_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, float rate)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLANCK_START_LAND_LEN];
    _mav_put_float(buf, 0, rate);
    _mav_put_uint8_t(buf, 4, target_system);
    _mav_put_uint8_t(buf, 5, target_component);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_START_LAND, buf, MAVLINK_MSG_ID_PLANCK_START_LAND_MIN_LEN, MAVLINK_MSG_ID_PLANCK_START_LAND_LEN, MAVLINK_MSG_ID_PLANCK_START_LAND_CRC);
#else
    mavlink_planck_start_land_t packet;
    packet.rate = rate;
    packet.target_system = target_system;
    packet.target_component = target_component;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_START_LAND, (const char *)&packet, MAVLINK_MSG_ID_PLANCK_START_LAND_MIN_LEN, MAVLINK_MSG_ID_PLANCK_START_LAND_LEN, MAVLINK_MSG_ID_PLANCK_START_LAND_CRC);
#endif
}

/**
 * @brief Send a planck_start_land message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_planck_start_land_send_struct(mavlink_channel_t chan, const mavlink_planck_start_land_t* planck_start_land)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_planck_start_land_send(chan, planck_start_land->target_system, planck_start_land->target_component, planck_start_land->rate);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_START_LAND, (const char *)planck_start_land, MAVLINK_MSG_ID_PLANCK_START_LAND_MIN_LEN, MAVLINK_MSG_ID_PLANCK_START_LAND_LEN, MAVLINK_MSG_ID_PLANCK_START_LAND_CRC);
#endif
}

#if MAVLINK_MSG_ID_PLANCK_START_LAND_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_planck_start_land_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t target_system, uint8_t target_component, float rate)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, rate);
    _mav_put_uint8_t(buf, 4, target_system);
    _mav_put_uint8_t(buf, 5, target_component);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_START_LAND, buf, MAVLINK_MSG_ID_PLANCK_START_LAND_MIN_LEN, MAVLINK_MSG_ID_PLANCK_START_LAND_LEN, MAVLINK_MSG_ID_PLANCK_START_LAND_CRC);
#else
    mavlink_planck_start_land_t *packet = (mavlink_planck_start_land_t *)msgbuf;
    packet->rate = rate;
    packet->target_system = target_system;
    packet->target_component = target_component;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_START_LAND, (const char *)packet, MAVLINK_MSG_ID_PLANCK_START_LAND_MIN_LEN, MAVLINK_MSG_ID_PLANCK_START_LAND_LEN, MAVLINK_MSG_ID_PLANCK_START_LAND_CRC);
#endif
}
#endif

#endif

// MESSAGE PLANCK_START_LAND UNPACKING


/**
 * @brief Get field target_system from planck_start_land message
 *
 * @return  System ID
 */
static inline uint8_t mavlink_msg_planck_start_land_get_target_system(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  4);
}

/**
 * @brief Get field target_component from planck_start_land message
 *
 * @return  Component ID
 */
static inline uint8_t mavlink_msg_planck_start_land_get_target_component(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  5);
}

/**
 * @brief Get field rate from planck_start_land message
 *
 * @return [m/s] Descent rate to use during landing
 */
static inline float mavlink_msg_planck_start_land_get_rate(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Decode a planck_start_land message into a struct
 *
 * @param msg The message to decode
 * @param planck_start_land C-struct to decode the message contents into
 */
static inline void mavlink_msg_planck_start_land_decode(const mavlink_message_t* msg, mavlink_planck_start_land_t* planck_start_land)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    planck_start_land->rate = mavlink_msg_planck_start_land_get_rate(msg);
    planck_start_land->target_system = mavlink_msg_planck_start_land_get_target_system(msg);
    planck_start_land->target_component = mavlink_msg_planck_start_land_get_target_component(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_PLANCK_START_LAND_LEN? msg->len : MAVLINK_MSG_ID_PLANCK_START_LAND_LEN;
        memset(planck_start_land, 0, MAVLINK_MSG_ID_PLANCK_START_LAND_LEN);
    memcpy(planck_start_land, _MAV_PAYLOAD(msg), len);
#endif
}
