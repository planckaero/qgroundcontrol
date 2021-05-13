#pragma once
// MESSAGE PLANCK_LANDING_TAG_ESTIMATE_NED PACKING

#define MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED 9006

MAVPACKED(
typedef struct __mavlink_planck_landing_tag_estimate_ned_t {
 uint64_t ap_timestamp_us; /*< [microseconds] Timestamp of the latest estimate in AP clock in microseconds*/
 uint32_t age; /*< [microseconds] Age of the latest measurement in microseconds*/
 float x; /*< [meters] X position of the tag relative to the CG of the aircraft in the NED frame*/
 float y; /*< [meters] Y position of the tag relative to the CG of the aircraft in the NED frame*/
 float z; /*< [meters] Z position of the tag relative to the CG of the aircraft in the NED frame*/
 float vx; /*< [m/s] X velocity of the tag relative to the CG of the aircraft in the NED frame*/
 float vy; /*< [m/s] Y velocity of the tag relative to the CG of the aircraft in the NED frame*/
 float vz; /*< [m/s] Z velocity of the tag relative to the CG of the aircraft in the NED frame*/
 float roll; /*< [rads] Euler angle roll of the tag in NED frame*/
 float pitch; /*< [rads] Euler angle pitch of the tag in NED frame*/
 float yaw; /*< [rads] Euler angle yaw of the tag in NED frame*/
 uint8_t target_system; /*<  System ID*/
 uint8_t target_component; /*<  Component ID*/
}) mavlink_planck_landing_tag_estimate_ned_t;

#define MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED_LEN 50
#define MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED_MIN_LEN 50
#define MAVLINK_MSG_ID_9006_LEN 50
#define MAVLINK_MSG_ID_9006_MIN_LEN 50

#define MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED_CRC 214
#define MAVLINK_MSG_ID_9006_CRC 214



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_PLANCK_LANDING_TAG_ESTIMATE_NED { \
    9006, \
    "PLANCK_LANDING_TAG_ESTIMATE_NED", \
    13, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 48, offsetof(mavlink_planck_landing_tag_estimate_ned_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 49, offsetof(mavlink_planck_landing_tag_estimate_ned_t, target_component) }, \
         { "age", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_planck_landing_tag_estimate_ned_t, age) }, \
         { "ap_timestamp_us", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_planck_landing_tag_estimate_ned_t, ap_timestamp_us) }, \
         { "x", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_planck_landing_tag_estimate_ned_t, x) }, \
         { "y", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_planck_landing_tag_estimate_ned_t, y) }, \
         { "z", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_planck_landing_tag_estimate_ned_t, z) }, \
         { "vx", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_planck_landing_tag_estimate_ned_t, vx) }, \
         { "vy", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_planck_landing_tag_estimate_ned_t, vy) }, \
         { "vz", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_planck_landing_tag_estimate_ned_t, vz) }, \
         { "roll", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_planck_landing_tag_estimate_ned_t, roll) }, \
         { "pitch", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_planck_landing_tag_estimate_ned_t, pitch) }, \
         { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_planck_landing_tag_estimate_ned_t, yaw) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_PLANCK_LANDING_TAG_ESTIMATE_NED { \
    "PLANCK_LANDING_TAG_ESTIMATE_NED", \
    13, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 48, offsetof(mavlink_planck_landing_tag_estimate_ned_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 49, offsetof(mavlink_planck_landing_tag_estimate_ned_t, target_component) }, \
         { "age", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_planck_landing_tag_estimate_ned_t, age) }, \
         { "ap_timestamp_us", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_planck_landing_tag_estimate_ned_t, ap_timestamp_us) }, \
         { "x", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_planck_landing_tag_estimate_ned_t, x) }, \
         { "y", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_planck_landing_tag_estimate_ned_t, y) }, \
         { "z", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_planck_landing_tag_estimate_ned_t, z) }, \
         { "vx", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_planck_landing_tag_estimate_ned_t, vx) }, \
         { "vy", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_planck_landing_tag_estimate_ned_t, vy) }, \
         { "vz", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_planck_landing_tag_estimate_ned_t, vz) }, \
         { "roll", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_planck_landing_tag_estimate_ned_t, roll) }, \
         { "pitch", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_planck_landing_tag_estimate_ned_t, pitch) }, \
         { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_planck_landing_tag_estimate_ned_t, yaw) }, \
         } \
}
#endif

/**
 * @brief Pack a planck_landing_tag_estimate_ned message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system  System ID
 * @param target_component  Component ID
 * @param age [microseconds] Age of the latest measurement in microseconds
 * @param ap_timestamp_us [microseconds] Timestamp of the latest estimate in AP clock in microseconds
 * @param x [meters] X position of the tag relative to the CG of the aircraft in the NED frame
 * @param y [meters] Y position of the tag relative to the CG of the aircraft in the NED frame
 * @param z [meters] Z position of the tag relative to the CG of the aircraft in the NED frame
 * @param vx [m/s] X velocity of the tag relative to the CG of the aircraft in the NED frame
 * @param vy [m/s] Y velocity of the tag relative to the CG of the aircraft in the NED frame
 * @param vz [m/s] Z velocity of the tag relative to the CG of the aircraft in the NED frame
 * @param roll [rads] Euler angle roll of the tag in NED frame
 * @param pitch [rads] Euler angle pitch of the tag in NED frame
 * @param yaw [rads] Euler angle yaw of the tag in NED frame
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_planck_landing_tag_estimate_ned_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t target_system, uint8_t target_component, uint32_t age, uint64_t ap_timestamp_us, float x, float y, float z, float vx, float vy, float vz, float roll, float pitch, float yaw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED_LEN];
    _mav_put_uint64_t(buf, 0, ap_timestamp_us);
    _mav_put_uint32_t(buf, 8, age);
    _mav_put_float(buf, 12, x);
    _mav_put_float(buf, 16, y);
    _mav_put_float(buf, 20, z);
    _mav_put_float(buf, 24, vx);
    _mav_put_float(buf, 28, vy);
    _mav_put_float(buf, 32, vz);
    _mav_put_float(buf, 36, roll);
    _mav_put_float(buf, 40, pitch);
    _mav_put_float(buf, 44, yaw);
    _mav_put_uint8_t(buf, 48, target_system);
    _mav_put_uint8_t(buf, 49, target_component);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED_LEN);
#else
    mavlink_planck_landing_tag_estimate_ned_t packet;
    packet.ap_timestamp_us = ap_timestamp_us;
    packet.age = age;
    packet.x = x;
    packet.y = y;
    packet.z = z;
    packet.vx = vx;
    packet.vy = vy;
    packet.vz = vz;
    packet.roll = roll;
    packet.pitch = pitch;
    packet.yaw = yaw;
    packet.target_system = target_system;
    packet.target_component = target_component;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED_MIN_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED_CRC);
}

/**
 * @brief Pack a planck_landing_tag_estimate_ned message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system  System ID
 * @param target_component  Component ID
 * @param age [microseconds] Age of the latest measurement in microseconds
 * @param ap_timestamp_us [microseconds] Timestamp of the latest estimate in AP clock in microseconds
 * @param x [meters] X position of the tag relative to the CG of the aircraft in the NED frame
 * @param y [meters] Y position of the tag relative to the CG of the aircraft in the NED frame
 * @param z [meters] Z position of the tag relative to the CG of the aircraft in the NED frame
 * @param vx [m/s] X velocity of the tag relative to the CG of the aircraft in the NED frame
 * @param vy [m/s] Y velocity of the tag relative to the CG of the aircraft in the NED frame
 * @param vz [m/s] Z velocity of the tag relative to the CG of the aircraft in the NED frame
 * @param roll [rads] Euler angle roll of the tag in NED frame
 * @param pitch [rads] Euler angle pitch of the tag in NED frame
 * @param yaw [rads] Euler angle yaw of the tag in NED frame
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_planck_landing_tag_estimate_ned_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t target_system,uint8_t target_component,uint32_t age,uint64_t ap_timestamp_us,float x,float y,float z,float vx,float vy,float vz,float roll,float pitch,float yaw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED_LEN];
    _mav_put_uint64_t(buf, 0, ap_timestamp_us);
    _mav_put_uint32_t(buf, 8, age);
    _mav_put_float(buf, 12, x);
    _mav_put_float(buf, 16, y);
    _mav_put_float(buf, 20, z);
    _mav_put_float(buf, 24, vx);
    _mav_put_float(buf, 28, vy);
    _mav_put_float(buf, 32, vz);
    _mav_put_float(buf, 36, roll);
    _mav_put_float(buf, 40, pitch);
    _mav_put_float(buf, 44, yaw);
    _mav_put_uint8_t(buf, 48, target_system);
    _mav_put_uint8_t(buf, 49, target_component);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED_LEN);
#else
    mavlink_planck_landing_tag_estimate_ned_t packet;
    packet.ap_timestamp_us = ap_timestamp_us;
    packet.age = age;
    packet.x = x;
    packet.y = y;
    packet.z = z;
    packet.vx = vx;
    packet.vy = vy;
    packet.vz = vz;
    packet.roll = roll;
    packet.pitch = pitch;
    packet.yaw = yaw;
    packet.target_system = target_system;
    packet.target_component = target_component;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED_MIN_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED_CRC);
}

/**
 * @brief Encode a planck_landing_tag_estimate_ned struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param planck_landing_tag_estimate_ned C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_planck_landing_tag_estimate_ned_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_planck_landing_tag_estimate_ned_t* planck_landing_tag_estimate_ned)
{
    return mavlink_msg_planck_landing_tag_estimate_ned_pack(system_id, component_id, msg, planck_landing_tag_estimate_ned->target_system, planck_landing_tag_estimate_ned->target_component, planck_landing_tag_estimate_ned->age, planck_landing_tag_estimate_ned->ap_timestamp_us, planck_landing_tag_estimate_ned->x, planck_landing_tag_estimate_ned->y, planck_landing_tag_estimate_ned->z, planck_landing_tag_estimate_ned->vx, planck_landing_tag_estimate_ned->vy, planck_landing_tag_estimate_ned->vz, planck_landing_tag_estimate_ned->roll, planck_landing_tag_estimate_ned->pitch, planck_landing_tag_estimate_ned->yaw);
}

/**
 * @brief Encode a planck_landing_tag_estimate_ned struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param planck_landing_tag_estimate_ned C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_planck_landing_tag_estimate_ned_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_planck_landing_tag_estimate_ned_t* planck_landing_tag_estimate_ned)
{
    return mavlink_msg_planck_landing_tag_estimate_ned_pack_chan(system_id, component_id, chan, msg, planck_landing_tag_estimate_ned->target_system, planck_landing_tag_estimate_ned->target_component, planck_landing_tag_estimate_ned->age, planck_landing_tag_estimate_ned->ap_timestamp_us, planck_landing_tag_estimate_ned->x, planck_landing_tag_estimate_ned->y, planck_landing_tag_estimate_ned->z, planck_landing_tag_estimate_ned->vx, planck_landing_tag_estimate_ned->vy, planck_landing_tag_estimate_ned->vz, planck_landing_tag_estimate_ned->roll, planck_landing_tag_estimate_ned->pitch, planck_landing_tag_estimate_ned->yaw);
}

/**
 * @brief Send a planck_landing_tag_estimate_ned message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system  System ID
 * @param target_component  Component ID
 * @param age [microseconds] Age of the latest measurement in microseconds
 * @param ap_timestamp_us [microseconds] Timestamp of the latest estimate in AP clock in microseconds
 * @param x [meters] X position of the tag relative to the CG of the aircraft in the NED frame
 * @param y [meters] Y position of the tag relative to the CG of the aircraft in the NED frame
 * @param z [meters] Z position of the tag relative to the CG of the aircraft in the NED frame
 * @param vx [m/s] X velocity of the tag relative to the CG of the aircraft in the NED frame
 * @param vy [m/s] Y velocity of the tag relative to the CG of the aircraft in the NED frame
 * @param vz [m/s] Z velocity of the tag relative to the CG of the aircraft in the NED frame
 * @param roll [rads] Euler angle roll of the tag in NED frame
 * @param pitch [rads] Euler angle pitch of the tag in NED frame
 * @param yaw [rads] Euler angle yaw of the tag in NED frame
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_planck_landing_tag_estimate_ned_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, uint32_t age, uint64_t ap_timestamp_us, float x, float y, float z, float vx, float vy, float vz, float roll, float pitch, float yaw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED_LEN];
    _mav_put_uint64_t(buf, 0, ap_timestamp_us);
    _mav_put_uint32_t(buf, 8, age);
    _mav_put_float(buf, 12, x);
    _mav_put_float(buf, 16, y);
    _mav_put_float(buf, 20, z);
    _mav_put_float(buf, 24, vx);
    _mav_put_float(buf, 28, vy);
    _mav_put_float(buf, 32, vz);
    _mav_put_float(buf, 36, roll);
    _mav_put_float(buf, 40, pitch);
    _mav_put_float(buf, 44, yaw);
    _mav_put_uint8_t(buf, 48, target_system);
    _mav_put_uint8_t(buf, 49, target_component);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED, buf, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED_MIN_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED_CRC);
#else
    mavlink_planck_landing_tag_estimate_ned_t packet;
    packet.ap_timestamp_us = ap_timestamp_us;
    packet.age = age;
    packet.x = x;
    packet.y = y;
    packet.z = z;
    packet.vx = vx;
    packet.vy = vy;
    packet.vz = vz;
    packet.roll = roll;
    packet.pitch = pitch;
    packet.yaw = yaw;
    packet.target_system = target_system;
    packet.target_component = target_component;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED, (const char *)&packet, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED_MIN_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED_CRC);
#endif
}

/**
 * @brief Send a planck_landing_tag_estimate_ned message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_planck_landing_tag_estimate_ned_send_struct(mavlink_channel_t chan, const mavlink_planck_landing_tag_estimate_ned_t* planck_landing_tag_estimate_ned)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_planck_landing_tag_estimate_ned_send(chan, planck_landing_tag_estimate_ned->target_system, planck_landing_tag_estimate_ned->target_component, planck_landing_tag_estimate_ned->age, planck_landing_tag_estimate_ned->ap_timestamp_us, planck_landing_tag_estimate_ned->x, planck_landing_tag_estimate_ned->y, planck_landing_tag_estimate_ned->z, planck_landing_tag_estimate_ned->vx, planck_landing_tag_estimate_ned->vy, planck_landing_tag_estimate_ned->vz, planck_landing_tag_estimate_ned->roll, planck_landing_tag_estimate_ned->pitch, planck_landing_tag_estimate_ned->yaw);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED, (const char *)planck_landing_tag_estimate_ned, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED_MIN_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED_CRC);
#endif
}

#if MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_planck_landing_tag_estimate_ned_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t target_system, uint8_t target_component, uint32_t age, uint64_t ap_timestamp_us, float x, float y, float z, float vx, float vy, float vz, float roll, float pitch, float yaw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, ap_timestamp_us);
    _mav_put_uint32_t(buf, 8, age);
    _mav_put_float(buf, 12, x);
    _mav_put_float(buf, 16, y);
    _mav_put_float(buf, 20, z);
    _mav_put_float(buf, 24, vx);
    _mav_put_float(buf, 28, vy);
    _mav_put_float(buf, 32, vz);
    _mav_put_float(buf, 36, roll);
    _mav_put_float(buf, 40, pitch);
    _mav_put_float(buf, 44, yaw);
    _mav_put_uint8_t(buf, 48, target_system);
    _mav_put_uint8_t(buf, 49, target_component);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED, buf, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED_MIN_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED_CRC);
#else
    mavlink_planck_landing_tag_estimate_ned_t *packet = (mavlink_planck_landing_tag_estimate_ned_t *)msgbuf;
    packet->ap_timestamp_us = ap_timestamp_us;
    packet->age = age;
    packet->x = x;
    packet->y = y;
    packet->z = z;
    packet->vx = vx;
    packet->vy = vy;
    packet->vz = vz;
    packet->roll = roll;
    packet->pitch = pitch;
    packet->yaw = yaw;
    packet->target_system = target_system;
    packet->target_component = target_component;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED, (const char *)packet, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED_MIN_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED_CRC);
#endif
}
#endif

#endif

// MESSAGE PLANCK_LANDING_TAG_ESTIMATE_NED UNPACKING


/**
 * @brief Get field target_system from planck_landing_tag_estimate_ned message
 *
 * @return  System ID
 */
static inline uint8_t mavlink_msg_planck_landing_tag_estimate_ned_get_target_system(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  48);
}

/**
 * @brief Get field target_component from planck_landing_tag_estimate_ned message
 *
 * @return  Component ID
 */
static inline uint8_t mavlink_msg_planck_landing_tag_estimate_ned_get_target_component(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  49);
}

/**
 * @brief Get field age from planck_landing_tag_estimate_ned message
 *
 * @return [microseconds] Age of the latest measurement in microseconds
 */
static inline uint32_t mavlink_msg_planck_landing_tag_estimate_ned_get_age(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  8);
}

/**
 * @brief Get field ap_timestamp_us from planck_landing_tag_estimate_ned message
 *
 * @return [microseconds] Timestamp of the latest estimate in AP clock in microseconds
 */
static inline uint64_t mavlink_msg_planck_landing_tag_estimate_ned_get_ap_timestamp_us(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field x from planck_landing_tag_estimate_ned message
 *
 * @return [meters] X position of the tag relative to the CG of the aircraft in the NED frame
 */
static inline float mavlink_msg_planck_landing_tag_estimate_ned_get_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field y from planck_landing_tag_estimate_ned message
 *
 * @return [meters] Y position of the tag relative to the CG of the aircraft in the NED frame
 */
static inline float mavlink_msg_planck_landing_tag_estimate_ned_get_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field z from planck_landing_tag_estimate_ned message
 *
 * @return [meters] Z position of the tag relative to the CG of the aircraft in the NED frame
 */
static inline float mavlink_msg_planck_landing_tag_estimate_ned_get_z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field vx from planck_landing_tag_estimate_ned message
 *
 * @return [m/s] X velocity of the tag relative to the CG of the aircraft in the NED frame
 */
static inline float mavlink_msg_planck_landing_tag_estimate_ned_get_vx(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field vy from planck_landing_tag_estimate_ned message
 *
 * @return [m/s] Y velocity of the tag relative to the CG of the aircraft in the NED frame
 */
static inline float mavlink_msg_planck_landing_tag_estimate_ned_get_vy(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field vz from planck_landing_tag_estimate_ned message
 *
 * @return [m/s] Z velocity of the tag relative to the CG of the aircraft in the NED frame
 */
static inline float mavlink_msg_planck_landing_tag_estimate_ned_get_vz(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Get field roll from planck_landing_tag_estimate_ned message
 *
 * @return [rads] Euler angle roll of the tag in NED frame
 */
static inline float mavlink_msg_planck_landing_tag_estimate_ned_get_roll(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  36);
}

/**
 * @brief Get field pitch from planck_landing_tag_estimate_ned message
 *
 * @return [rads] Euler angle pitch of the tag in NED frame
 */
static inline float mavlink_msg_planck_landing_tag_estimate_ned_get_pitch(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  40);
}

/**
 * @brief Get field yaw from planck_landing_tag_estimate_ned message
 *
 * @return [rads] Euler angle yaw of the tag in NED frame
 */
static inline float mavlink_msg_planck_landing_tag_estimate_ned_get_yaw(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  44);
}

/**
 * @brief Decode a planck_landing_tag_estimate_ned message into a struct
 *
 * @param msg The message to decode
 * @param planck_landing_tag_estimate_ned C-struct to decode the message contents into
 */
static inline void mavlink_msg_planck_landing_tag_estimate_ned_decode(const mavlink_message_t* msg, mavlink_planck_landing_tag_estimate_ned_t* planck_landing_tag_estimate_ned)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    planck_landing_tag_estimate_ned->ap_timestamp_us = mavlink_msg_planck_landing_tag_estimate_ned_get_ap_timestamp_us(msg);
    planck_landing_tag_estimate_ned->age = mavlink_msg_planck_landing_tag_estimate_ned_get_age(msg);
    planck_landing_tag_estimate_ned->x = mavlink_msg_planck_landing_tag_estimate_ned_get_x(msg);
    planck_landing_tag_estimate_ned->y = mavlink_msg_planck_landing_tag_estimate_ned_get_y(msg);
    planck_landing_tag_estimate_ned->z = mavlink_msg_planck_landing_tag_estimate_ned_get_z(msg);
    planck_landing_tag_estimate_ned->vx = mavlink_msg_planck_landing_tag_estimate_ned_get_vx(msg);
    planck_landing_tag_estimate_ned->vy = mavlink_msg_planck_landing_tag_estimate_ned_get_vy(msg);
    planck_landing_tag_estimate_ned->vz = mavlink_msg_planck_landing_tag_estimate_ned_get_vz(msg);
    planck_landing_tag_estimate_ned->roll = mavlink_msg_planck_landing_tag_estimate_ned_get_roll(msg);
    planck_landing_tag_estimate_ned->pitch = mavlink_msg_planck_landing_tag_estimate_ned_get_pitch(msg);
    planck_landing_tag_estimate_ned->yaw = mavlink_msg_planck_landing_tag_estimate_ned_get_yaw(msg);
    planck_landing_tag_estimate_ned->target_system = mavlink_msg_planck_landing_tag_estimate_ned_get_target_system(msg);
    planck_landing_tag_estimate_ned->target_component = mavlink_msg_planck_landing_tag_estimate_ned_get_target_component(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED_LEN? msg->len : MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED_LEN;
        memset(planck_landing_tag_estimate_ned, 0, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED_LEN);
    memcpy(planck_landing_tag_estimate_ned, _MAV_PAYLOAD(msg), len);
#endif
}
