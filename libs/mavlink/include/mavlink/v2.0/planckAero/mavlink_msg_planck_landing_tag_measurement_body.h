#pragma once
// MESSAGE PLANCK_LANDING_TAG_MEASUREMENT_BODY PACKING

#define MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY 9007

MAVPACKED(
typedef struct __mavlink_planck_landing_tag_measurement_body_t {
 uint64_t ap_timestamp_us; /*< [microseconds] Timestamp of this measurement in AP clock in microseconds*/
 uint32_t age; /*< [microseconds] Age of the latest measurement in microseconds*/
 float x; /*< [meters] X position of the tag relative to the CG of the aircraft in the body frame*/
 float y; /*< [meters] Y position of the tag relative to the CG of the aircraft in the body frame*/
 float z; /*< [meters] Z position of the tag relative to the CG of the aircraft in the body frame*/
 float roll; /*< [rads] Euler angle roll of the tag in body frame*/
 float pitch; /*< [rads] Euler angle pitch of the tag in body frame*/
 float yaw; /*< [rads] Euler angle yaw of the tag in body frame*/
 uint8_t target_system; /*<  System ID*/
 uint8_t target_component; /*<  Component ID*/
}) mavlink_planck_landing_tag_measurement_body_t;

#define MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY_LEN 38
#define MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY_MIN_LEN 38
#define MAVLINK_MSG_ID_9007_LEN 38
#define MAVLINK_MSG_ID_9007_MIN_LEN 38

#define MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY_CRC 162
#define MAVLINK_MSG_ID_9007_CRC 162



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_PLANCK_LANDING_TAG_MEASUREMENT_BODY { \
    9007, \
    "PLANCK_LANDING_TAG_MEASUREMENT_BODY", \
    10, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 36, offsetof(mavlink_planck_landing_tag_measurement_body_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 37, offsetof(mavlink_planck_landing_tag_measurement_body_t, target_component) }, \
         { "age", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_planck_landing_tag_measurement_body_t, age) }, \
         { "ap_timestamp_us", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_planck_landing_tag_measurement_body_t, ap_timestamp_us) }, \
         { "x", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_planck_landing_tag_measurement_body_t, x) }, \
         { "y", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_planck_landing_tag_measurement_body_t, y) }, \
         { "z", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_planck_landing_tag_measurement_body_t, z) }, \
         { "roll", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_planck_landing_tag_measurement_body_t, roll) }, \
         { "pitch", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_planck_landing_tag_measurement_body_t, pitch) }, \
         { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_planck_landing_tag_measurement_body_t, yaw) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_PLANCK_LANDING_TAG_MEASUREMENT_BODY { \
    "PLANCK_LANDING_TAG_MEASUREMENT_BODY", \
    10, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 36, offsetof(mavlink_planck_landing_tag_measurement_body_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 37, offsetof(mavlink_planck_landing_tag_measurement_body_t, target_component) }, \
         { "age", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_planck_landing_tag_measurement_body_t, age) }, \
         { "ap_timestamp_us", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_planck_landing_tag_measurement_body_t, ap_timestamp_us) }, \
         { "x", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_planck_landing_tag_measurement_body_t, x) }, \
         { "y", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_planck_landing_tag_measurement_body_t, y) }, \
         { "z", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_planck_landing_tag_measurement_body_t, z) }, \
         { "roll", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_planck_landing_tag_measurement_body_t, roll) }, \
         { "pitch", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_planck_landing_tag_measurement_body_t, pitch) }, \
         { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_planck_landing_tag_measurement_body_t, yaw) }, \
         } \
}
#endif

/**
 * @brief Pack a planck_landing_tag_measurement_body message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system  System ID
 * @param target_component  Component ID
 * @param age [microseconds] Age of the latest measurement in microseconds
 * @param ap_timestamp_us [microseconds] Timestamp of this measurement in AP clock in microseconds
 * @param x [meters] X position of the tag relative to the CG of the aircraft in the body frame
 * @param y [meters] Y position of the tag relative to the CG of the aircraft in the body frame
 * @param z [meters] Z position of the tag relative to the CG of the aircraft in the body frame
 * @param roll [rads] Euler angle roll of the tag in body frame
 * @param pitch [rads] Euler angle pitch of the tag in body frame
 * @param yaw [rads] Euler angle yaw of the tag in body frame
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_planck_landing_tag_measurement_body_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t target_system, uint8_t target_component, uint32_t age, uint64_t ap_timestamp_us, float x, float y, float z, float roll, float pitch, float yaw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY_LEN];
    _mav_put_uint64_t(buf, 0, ap_timestamp_us);
    _mav_put_uint32_t(buf, 8, age);
    _mav_put_float(buf, 12, x);
    _mav_put_float(buf, 16, y);
    _mav_put_float(buf, 20, z);
    _mav_put_float(buf, 24, roll);
    _mav_put_float(buf, 28, pitch);
    _mav_put_float(buf, 32, yaw);
    _mav_put_uint8_t(buf, 36, target_system);
    _mav_put_uint8_t(buf, 37, target_component);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY_LEN);
#else
    mavlink_planck_landing_tag_measurement_body_t packet;
    packet.ap_timestamp_us = ap_timestamp_us;
    packet.age = age;
    packet.x = x;
    packet.y = y;
    packet.z = z;
    packet.roll = roll;
    packet.pitch = pitch;
    packet.yaw = yaw;
    packet.target_system = target_system;
    packet.target_component = target_component;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY_MIN_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY_CRC);
}

/**
 * @brief Pack a planck_landing_tag_measurement_body message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system  System ID
 * @param target_component  Component ID
 * @param age [microseconds] Age of the latest measurement in microseconds
 * @param ap_timestamp_us [microseconds] Timestamp of this measurement in AP clock in microseconds
 * @param x [meters] X position of the tag relative to the CG of the aircraft in the body frame
 * @param y [meters] Y position of the tag relative to the CG of the aircraft in the body frame
 * @param z [meters] Z position of the tag relative to the CG of the aircraft in the body frame
 * @param roll [rads] Euler angle roll of the tag in body frame
 * @param pitch [rads] Euler angle pitch of the tag in body frame
 * @param yaw [rads] Euler angle yaw of the tag in body frame
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_planck_landing_tag_measurement_body_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t target_system,uint8_t target_component,uint32_t age,uint64_t ap_timestamp_us,float x,float y,float z,float roll,float pitch,float yaw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY_LEN];
    _mav_put_uint64_t(buf, 0, ap_timestamp_us);
    _mav_put_uint32_t(buf, 8, age);
    _mav_put_float(buf, 12, x);
    _mav_put_float(buf, 16, y);
    _mav_put_float(buf, 20, z);
    _mav_put_float(buf, 24, roll);
    _mav_put_float(buf, 28, pitch);
    _mav_put_float(buf, 32, yaw);
    _mav_put_uint8_t(buf, 36, target_system);
    _mav_put_uint8_t(buf, 37, target_component);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY_LEN);
#else
    mavlink_planck_landing_tag_measurement_body_t packet;
    packet.ap_timestamp_us = ap_timestamp_us;
    packet.age = age;
    packet.x = x;
    packet.y = y;
    packet.z = z;
    packet.roll = roll;
    packet.pitch = pitch;
    packet.yaw = yaw;
    packet.target_system = target_system;
    packet.target_component = target_component;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY_MIN_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY_CRC);
}

/**
 * @brief Encode a planck_landing_tag_measurement_body struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param planck_landing_tag_measurement_body C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_planck_landing_tag_measurement_body_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_planck_landing_tag_measurement_body_t* planck_landing_tag_measurement_body)
{
    return mavlink_msg_planck_landing_tag_measurement_body_pack(system_id, component_id, msg, planck_landing_tag_measurement_body->target_system, planck_landing_tag_measurement_body->target_component, planck_landing_tag_measurement_body->age, planck_landing_tag_measurement_body->ap_timestamp_us, planck_landing_tag_measurement_body->x, planck_landing_tag_measurement_body->y, planck_landing_tag_measurement_body->z, planck_landing_tag_measurement_body->roll, planck_landing_tag_measurement_body->pitch, planck_landing_tag_measurement_body->yaw);
}

/**
 * @brief Encode a planck_landing_tag_measurement_body struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param planck_landing_tag_measurement_body C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_planck_landing_tag_measurement_body_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_planck_landing_tag_measurement_body_t* planck_landing_tag_measurement_body)
{
    return mavlink_msg_planck_landing_tag_measurement_body_pack_chan(system_id, component_id, chan, msg, planck_landing_tag_measurement_body->target_system, planck_landing_tag_measurement_body->target_component, planck_landing_tag_measurement_body->age, planck_landing_tag_measurement_body->ap_timestamp_us, planck_landing_tag_measurement_body->x, planck_landing_tag_measurement_body->y, planck_landing_tag_measurement_body->z, planck_landing_tag_measurement_body->roll, planck_landing_tag_measurement_body->pitch, planck_landing_tag_measurement_body->yaw);
}

/**
 * @brief Send a planck_landing_tag_measurement_body message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system  System ID
 * @param target_component  Component ID
 * @param age [microseconds] Age of the latest measurement in microseconds
 * @param ap_timestamp_us [microseconds] Timestamp of this measurement in AP clock in microseconds
 * @param x [meters] X position of the tag relative to the CG of the aircraft in the body frame
 * @param y [meters] Y position of the tag relative to the CG of the aircraft in the body frame
 * @param z [meters] Z position of the tag relative to the CG of the aircraft in the body frame
 * @param roll [rads] Euler angle roll of the tag in body frame
 * @param pitch [rads] Euler angle pitch of the tag in body frame
 * @param yaw [rads] Euler angle yaw of the tag in body frame
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_planck_landing_tag_measurement_body_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, uint32_t age, uint64_t ap_timestamp_us, float x, float y, float z, float roll, float pitch, float yaw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY_LEN];
    _mav_put_uint64_t(buf, 0, ap_timestamp_us);
    _mav_put_uint32_t(buf, 8, age);
    _mav_put_float(buf, 12, x);
    _mav_put_float(buf, 16, y);
    _mav_put_float(buf, 20, z);
    _mav_put_float(buf, 24, roll);
    _mav_put_float(buf, 28, pitch);
    _mav_put_float(buf, 32, yaw);
    _mav_put_uint8_t(buf, 36, target_system);
    _mav_put_uint8_t(buf, 37, target_component);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY, buf, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY_MIN_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY_CRC);
#else
    mavlink_planck_landing_tag_measurement_body_t packet;
    packet.ap_timestamp_us = ap_timestamp_us;
    packet.age = age;
    packet.x = x;
    packet.y = y;
    packet.z = z;
    packet.roll = roll;
    packet.pitch = pitch;
    packet.yaw = yaw;
    packet.target_system = target_system;
    packet.target_component = target_component;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY, (const char *)&packet, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY_MIN_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY_CRC);
#endif
}

/**
 * @brief Send a planck_landing_tag_measurement_body message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_planck_landing_tag_measurement_body_send_struct(mavlink_channel_t chan, const mavlink_planck_landing_tag_measurement_body_t* planck_landing_tag_measurement_body)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_planck_landing_tag_measurement_body_send(chan, planck_landing_tag_measurement_body->target_system, planck_landing_tag_measurement_body->target_component, planck_landing_tag_measurement_body->age, planck_landing_tag_measurement_body->ap_timestamp_us, planck_landing_tag_measurement_body->x, planck_landing_tag_measurement_body->y, planck_landing_tag_measurement_body->z, planck_landing_tag_measurement_body->roll, planck_landing_tag_measurement_body->pitch, planck_landing_tag_measurement_body->yaw);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY, (const char *)planck_landing_tag_measurement_body, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY_MIN_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY_CRC);
#endif
}

#if MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_planck_landing_tag_measurement_body_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t target_system, uint8_t target_component, uint32_t age, uint64_t ap_timestamp_us, float x, float y, float z, float roll, float pitch, float yaw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, ap_timestamp_us);
    _mav_put_uint32_t(buf, 8, age);
    _mav_put_float(buf, 12, x);
    _mav_put_float(buf, 16, y);
    _mav_put_float(buf, 20, z);
    _mav_put_float(buf, 24, roll);
    _mav_put_float(buf, 28, pitch);
    _mav_put_float(buf, 32, yaw);
    _mav_put_uint8_t(buf, 36, target_system);
    _mav_put_uint8_t(buf, 37, target_component);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY, buf, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY_MIN_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY_CRC);
#else
    mavlink_planck_landing_tag_measurement_body_t *packet = (mavlink_planck_landing_tag_measurement_body_t *)msgbuf;
    packet->ap_timestamp_us = ap_timestamp_us;
    packet->age = age;
    packet->x = x;
    packet->y = y;
    packet->z = z;
    packet->roll = roll;
    packet->pitch = pitch;
    packet->yaw = yaw;
    packet->target_system = target_system;
    packet->target_component = target_component;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY, (const char *)packet, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY_MIN_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY_CRC);
#endif
}
#endif

#endif

// MESSAGE PLANCK_LANDING_TAG_MEASUREMENT_BODY UNPACKING


/**
 * @brief Get field target_system from planck_landing_tag_measurement_body message
 *
 * @return  System ID
 */
static inline uint8_t mavlink_msg_planck_landing_tag_measurement_body_get_target_system(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  36);
}

/**
 * @brief Get field target_component from planck_landing_tag_measurement_body message
 *
 * @return  Component ID
 */
static inline uint8_t mavlink_msg_planck_landing_tag_measurement_body_get_target_component(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  37);
}

/**
 * @brief Get field age from planck_landing_tag_measurement_body message
 *
 * @return [microseconds] Age of the latest measurement in microseconds
 */
static inline uint32_t mavlink_msg_planck_landing_tag_measurement_body_get_age(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  8);
}

/**
 * @brief Get field ap_timestamp_us from planck_landing_tag_measurement_body message
 *
 * @return [microseconds] Timestamp of this measurement in AP clock in microseconds
 */
static inline uint64_t mavlink_msg_planck_landing_tag_measurement_body_get_ap_timestamp_us(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field x from planck_landing_tag_measurement_body message
 *
 * @return [meters] X position of the tag relative to the CG of the aircraft in the body frame
 */
static inline float mavlink_msg_planck_landing_tag_measurement_body_get_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field y from planck_landing_tag_measurement_body message
 *
 * @return [meters] Y position of the tag relative to the CG of the aircraft in the body frame
 */
static inline float mavlink_msg_planck_landing_tag_measurement_body_get_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field z from planck_landing_tag_measurement_body message
 *
 * @return [meters] Z position of the tag relative to the CG of the aircraft in the body frame
 */
static inline float mavlink_msg_planck_landing_tag_measurement_body_get_z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field roll from planck_landing_tag_measurement_body message
 *
 * @return [rads] Euler angle roll of the tag in body frame
 */
static inline float mavlink_msg_planck_landing_tag_measurement_body_get_roll(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field pitch from planck_landing_tag_measurement_body message
 *
 * @return [rads] Euler angle pitch of the tag in body frame
 */
static inline float mavlink_msg_planck_landing_tag_measurement_body_get_pitch(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field yaw from planck_landing_tag_measurement_body message
 *
 * @return [rads] Euler angle yaw of the tag in body frame
 */
static inline float mavlink_msg_planck_landing_tag_measurement_body_get_yaw(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Decode a planck_landing_tag_measurement_body message into a struct
 *
 * @param msg The message to decode
 * @param planck_landing_tag_measurement_body C-struct to decode the message contents into
 */
static inline void mavlink_msg_planck_landing_tag_measurement_body_decode(const mavlink_message_t* msg, mavlink_planck_landing_tag_measurement_body_t* planck_landing_tag_measurement_body)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    planck_landing_tag_measurement_body->ap_timestamp_us = mavlink_msg_planck_landing_tag_measurement_body_get_ap_timestamp_us(msg);
    planck_landing_tag_measurement_body->age = mavlink_msg_planck_landing_tag_measurement_body_get_age(msg);
    planck_landing_tag_measurement_body->x = mavlink_msg_planck_landing_tag_measurement_body_get_x(msg);
    planck_landing_tag_measurement_body->y = mavlink_msg_planck_landing_tag_measurement_body_get_y(msg);
    planck_landing_tag_measurement_body->z = mavlink_msg_planck_landing_tag_measurement_body_get_z(msg);
    planck_landing_tag_measurement_body->roll = mavlink_msg_planck_landing_tag_measurement_body_get_roll(msg);
    planck_landing_tag_measurement_body->pitch = mavlink_msg_planck_landing_tag_measurement_body_get_pitch(msg);
    planck_landing_tag_measurement_body->yaw = mavlink_msg_planck_landing_tag_measurement_body_get_yaw(msg);
    planck_landing_tag_measurement_body->target_system = mavlink_msg_planck_landing_tag_measurement_body_get_target_system(msg);
    planck_landing_tag_measurement_body->target_component = mavlink_msg_planck_landing_tag_measurement_body_get_target_component(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY_LEN? msg->len : MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY_LEN;
        memset(planck_landing_tag_measurement_body, 0, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY_LEN);
    memcpy(planck_landing_tag_measurement_body, _MAV_PAYLOAD(msg), len);
#endif
}
