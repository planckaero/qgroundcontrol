#pragma once
// MESSAGE PLANCK_LANDING_PLATFORM_STATE PACKING

#define MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE 9002

MAVPACKED(
typedef struct __mavlink_planck_landing_platform_state_t {
 int32_t latitude; /*<  Latitude (WGS84), in degrees * 1E7*/
 int32_t longitude; /*<  Longitude (WGS84, in degrees * 1E7*/
 int32_t altitude; /*<  Altitude (AMSL), in meters * 1000 (positive for up)*/
 float vn; /*<  GPS velocity in m/s in NORTH direction in earth-fixed NED frame*/
 float ve; /*<  GPS velocity in m/s in EAST direction in earth-fixed NED frame*/
 float vd; /*<  GPS velocity in m/s in DOWN direction in earth-fixed NED frame*/
 float roll; /*<  Roll in degrees of the platform*/
 float pitch; /*<  Pitch in degrees of the platform*/
 float yaw; /*<  Yaw in degrees of the platform*/
}) mavlink_planck_landing_platform_state_t;

#define MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE_LEN 36
#define MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE_MIN_LEN 36
#define MAVLINK_MSG_ID_9002_LEN 36
#define MAVLINK_MSG_ID_9002_MIN_LEN 36

#define MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE_CRC 228
#define MAVLINK_MSG_ID_9002_CRC 228



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_PLANCK_LANDING_PLATFORM_STATE { \
    9002, \
    "PLANCK_LANDING_PLATFORM_STATE", \
    9, \
    {  { "latitude", NULL, MAVLINK_TYPE_INT32_T, 0, 0, offsetof(mavlink_planck_landing_platform_state_t, latitude) }, \
         { "longitude", NULL, MAVLINK_TYPE_INT32_T, 0, 4, offsetof(mavlink_planck_landing_platform_state_t, longitude) }, \
         { "altitude", NULL, MAVLINK_TYPE_INT32_T, 0, 8, offsetof(mavlink_planck_landing_platform_state_t, altitude) }, \
         { "vn", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_planck_landing_platform_state_t, vn) }, \
         { "ve", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_planck_landing_platform_state_t, ve) }, \
         { "vd", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_planck_landing_platform_state_t, vd) }, \
         { "roll", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_planck_landing_platform_state_t, roll) }, \
         { "pitch", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_planck_landing_platform_state_t, pitch) }, \
         { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_planck_landing_platform_state_t, yaw) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_PLANCK_LANDING_PLATFORM_STATE { \
    "PLANCK_LANDING_PLATFORM_STATE", \
    9, \
    {  { "latitude", NULL, MAVLINK_TYPE_INT32_T, 0, 0, offsetof(mavlink_planck_landing_platform_state_t, latitude) }, \
         { "longitude", NULL, MAVLINK_TYPE_INT32_T, 0, 4, offsetof(mavlink_planck_landing_platform_state_t, longitude) }, \
         { "altitude", NULL, MAVLINK_TYPE_INT32_T, 0, 8, offsetof(mavlink_planck_landing_platform_state_t, altitude) }, \
         { "vn", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_planck_landing_platform_state_t, vn) }, \
         { "ve", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_planck_landing_platform_state_t, ve) }, \
         { "vd", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_planck_landing_platform_state_t, vd) }, \
         { "roll", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_planck_landing_platform_state_t, roll) }, \
         { "pitch", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_planck_landing_platform_state_t, pitch) }, \
         { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_planck_landing_platform_state_t, yaw) }, \
         } \
}
#endif

/**
 * @brief Pack a planck_landing_platform_state message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param latitude  Latitude (WGS84), in degrees * 1E7
 * @param longitude  Longitude (WGS84, in degrees * 1E7
 * @param altitude  Altitude (AMSL), in meters * 1000 (positive for up)
 * @param vn  GPS velocity in m/s in NORTH direction in earth-fixed NED frame
 * @param ve  GPS velocity in m/s in EAST direction in earth-fixed NED frame
 * @param vd  GPS velocity in m/s in DOWN direction in earth-fixed NED frame
 * @param roll  Roll in degrees of the platform
 * @param pitch  Pitch in degrees of the platform
 * @param yaw  Yaw in degrees of the platform
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_planck_landing_platform_state_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               int32_t latitude, int32_t longitude, int32_t altitude, float vn, float ve, float vd, float roll, float pitch, float yaw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE_LEN];
    _mav_put_int32_t(buf, 0, latitude);
    _mav_put_int32_t(buf, 4, longitude);
    _mav_put_int32_t(buf, 8, altitude);
    _mav_put_float(buf, 12, vn);
    _mav_put_float(buf, 16, ve);
    _mav_put_float(buf, 20, vd);
    _mav_put_float(buf, 24, roll);
    _mav_put_float(buf, 28, pitch);
    _mav_put_float(buf, 32, yaw);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE_LEN);
#else
    mavlink_planck_landing_platform_state_t packet;
    packet.latitude = latitude;
    packet.longitude = longitude;
    packet.altitude = altitude;
    packet.vn = vn;
    packet.ve = ve;
    packet.vd = vd;
    packet.roll = roll;
    packet.pitch = pitch;
    packet.yaw = yaw;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE_MIN_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE_CRC);
}

/**
 * @brief Pack a planck_landing_platform_state message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param latitude  Latitude (WGS84), in degrees * 1E7
 * @param longitude  Longitude (WGS84, in degrees * 1E7
 * @param altitude  Altitude (AMSL), in meters * 1000 (positive for up)
 * @param vn  GPS velocity in m/s in NORTH direction in earth-fixed NED frame
 * @param ve  GPS velocity in m/s in EAST direction in earth-fixed NED frame
 * @param vd  GPS velocity in m/s in DOWN direction in earth-fixed NED frame
 * @param roll  Roll in degrees of the platform
 * @param pitch  Pitch in degrees of the platform
 * @param yaw  Yaw in degrees of the platform
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_planck_landing_platform_state_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   int32_t latitude,int32_t longitude,int32_t altitude,float vn,float ve,float vd,float roll,float pitch,float yaw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE_LEN];
    _mav_put_int32_t(buf, 0, latitude);
    _mav_put_int32_t(buf, 4, longitude);
    _mav_put_int32_t(buf, 8, altitude);
    _mav_put_float(buf, 12, vn);
    _mav_put_float(buf, 16, ve);
    _mav_put_float(buf, 20, vd);
    _mav_put_float(buf, 24, roll);
    _mav_put_float(buf, 28, pitch);
    _mav_put_float(buf, 32, yaw);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE_LEN);
#else
    mavlink_planck_landing_platform_state_t packet;
    packet.latitude = latitude;
    packet.longitude = longitude;
    packet.altitude = altitude;
    packet.vn = vn;
    packet.ve = ve;
    packet.vd = vd;
    packet.roll = roll;
    packet.pitch = pitch;
    packet.yaw = yaw;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE_MIN_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE_CRC);
}

/**
 * @brief Encode a planck_landing_platform_state struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param planck_landing_platform_state C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_planck_landing_platform_state_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_planck_landing_platform_state_t* planck_landing_platform_state)
{
    return mavlink_msg_planck_landing_platform_state_pack(system_id, component_id, msg, planck_landing_platform_state->latitude, planck_landing_platform_state->longitude, planck_landing_platform_state->altitude, planck_landing_platform_state->vn, planck_landing_platform_state->ve, planck_landing_platform_state->vd, planck_landing_platform_state->roll, planck_landing_platform_state->pitch, planck_landing_platform_state->yaw);
}

/**
 * @brief Encode a planck_landing_platform_state struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param planck_landing_platform_state C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_planck_landing_platform_state_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_planck_landing_platform_state_t* planck_landing_platform_state)
{
    return mavlink_msg_planck_landing_platform_state_pack_chan(system_id, component_id, chan, msg, planck_landing_platform_state->latitude, planck_landing_platform_state->longitude, planck_landing_platform_state->altitude, planck_landing_platform_state->vn, planck_landing_platform_state->ve, planck_landing_platform_state->vd, planck_landing_platform_state->roll, planck_landing_platform_state->pitch, planck_landing_platform_state->yaw);
}

/**
 * @brief Send a planck_landing_platform_state message
 * @param chan MAVLink channel to send the message
 *
 * @param latitude  Latitude (WGS84), in degrees * 1E7
 * @param longitude  Longitude (WGS84, in degrees * 1E7
 * @param altitude  Altitude (AMSL), in meters * 1000 (positive for up)
 * @param vn  GPS velocity in m/s in NORTH direction in earth-fixed NED frame
 * @param ve  GPS velocity in m/s in EAST direction in earth-fixed NED frame
 * @param vd  GPS velocity in m/s in DOWN direction in earth-fixed NED frame
 * @param roll  Roll in degrees of the platform
 * @param pitch  Pitch in degrees of the platform
 * @param yaw  Yaw in degrees of the platform
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_planck_landing_platform_state_send(mavlink_channel_t chan, int32_t latitude, int32_t longitude, int32_t altitude, float vn, float ve, float vd, float roll, float pitch, float yaw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE_LEN];
    _mav_put_int32_t(buf, 0, latitude);
    _mav_put_int32_t(buf, 4, longitude);
    _mav_put_int32_t(buf, 8, altitude);
    _mav_put_float(buf, 12, vn);
    _mav_put_float(buf, 16, ve);
    _mav_put_float(buf, 20, vd);
    _mav_put_float(buf, 24, roll);
    _mav_put_float(buf, 28, pitch);
    _mav_put_float(buf, 32, yaw);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE, buf, MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE_MIN_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE_CRC);
#else
    mavlink_planck_landing_platform_state_t packet;
    packet.latitude = latitude;
    packet.longitude = longitude;
    packet.altitude = altitude;
    packet.vn = vn;
    packet.ve = ve;
    packet.vd = vd;
    packet.roll = roll;
    packet.pitch = pitch;
    packet.yaw = yaw;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE, (const char *)&packet, MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE_MIN_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE_CRC);
#endif
}

/**
 * @brief Send a planck_landing_platform_state message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_planck_landing_platform_state_send_struct(mavlink_channel_t chan, const mavlink_planck_landing_platform_state_t* planck_landing_platform_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_planck_landing_platform_state_send(chan, planck_landing_platform_state->latitude, planck_landing_platform_state->longitude, planck_landing_platform_state->altitude, planck_landing_platform_state->vn, planck_landing_platform_state->ve, planck_landing_platform_state->vd, planck_landing_platform_state->roll, planck_landing_platform_state->pitch, planck_landing_platform_state->yaw);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE, (const char *)planck_landing_platform_state, MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE_MIN_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE_CRC);
#endif
}

#if MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_planck_landing_platform_state_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  int32_t latitude, int32_t longitude, int32_t altitude, float vn, float ve, float vd, float roll, float pitch, float yaw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int32_t(buf, 0, latitude);
    _mav_put_int32_t(buf, 4, longitude);
    _mav_put_int32_t(buf, 8, altitude);
    _mav_put_float(buf, 12, vn);
    _mav_put_float(buf, 16, ve);
    _mav_put_float(buf, 20, vd);
    _mav_put_float(buf, 24, roll);
    _mav_put_float(buf, 28, pitch);
    _mav_put_float(buf, 32, yaw);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE, buf, MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE_MIN_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE_CRC);
#else
    mavlink_planck_landing_platform_state_t *packet = (mavlink_planck_landing_platform_state_t *)msgbuf;
    packet->latitude = latitude;
    packet->longitude = longitude;
    packet->altitude = altitude;
    packet->vn = vn;
    packet->ve = ve;
    packet->vd = vd;
    packet->roll = roll;
    packet->pitch = pitch;
    packet->yaw = yaw;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE, (const char *)packet, MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE_MIN_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE_CRC);
#endif
}
#endif

#endif

// MESSAGE PLANCK_LANDING_PLATFORM_STATE UNPACKING


/**
 * @brief Get field latitude from planck_landing_platform_state message
 *
 * @return  Latitude (WGS84), in degrees * 1E7
 */
static inline int32_t mavlink_msg_planck_landing_platform_state_get_latitude(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  0);
}

/**
 * @brief Get field longitude from planck_landing_platform_state message
 *
 * @return  Longitude (WGS84, in degrees * 1E7
 */
static inline int32_t mavlink_msg_planck_landing_platform_state_get_longitude(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  4);
}

/**
 * @brief Get field altitude from planck_landing_platform_state message
 *
 * @return  Altitude (AMSL), in meters * 1000 (positive for up)
 */
static inline int32_t mavlink_msg_planck_landing_platform_state_get_altitude(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  8);
}

/**
 * @brief Get field vn from planck_landing_platform_state message
 *
 * @return  GPS velocity in m/s in NORTH direction in earth-fixed NED frame
 */
static inline float mavlink_msg_planck_landing_platform_state_get_vn(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field ve from planck_landing_platform_state message
 *
 * @return  GPS velocity in m/s in EAST direction in earth-fixed NED frame
 */
static inline float mavlink_msg_planck_landing_platform_state_get_ve(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field vd from planck_landing_platform_state message
 *
 * @return  GPS velocity in m/s in DOWN direction in earth-fixed NED frame
 */
static inline float mavlink_msg_planck_landing_platform_state_get_vd(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field roll from planck_landing_platform_state message
 *
 * @return  Roll in degrees of the platform
 */
static inline float mavlink_msg_planck_landing_platform_state_get_roll(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field pitch from planck_landing_platform_state message
 *
 * @return  Pitch in degrees of the platform
 */
static inline float mavlink_msg_planck_landing_platform_state_get_pitch(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field yaw from planck_landing_platform_state message
 *
 * @return  Yaw in degrees of the platform
 */
static inline float mavlink_msg_planck_landing_platform_state_get_yaw(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Decode a planck_landing_platform_state message into a struct
 *
 * @param msg The message to decode
 * @param planck_landing_platform_state C-struct to decode the message contents into
 */
static inline void mavlink_msg_planck_landing_platform_state_decode(const mavlink_message_t* msg, mavlink_planck_landing_platform_state_t* planck_landing_platform_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    planck_landing_platform_state->latitude = mavlink_msg_planck_landing_platform_state_get_latitude(msg);
    planck_landing_platform_state->longitude = mavlink_msg_planck_landing_platform_state_get_longitude(msg);
    planck_landing_platform_state->altitude = mavlink_msg_planck_landing_platform_state_get_altitude(msg);
    planck_landing_platform_state->vn = mavlink_msg_planck_landing_platform_state_get_vn(msg);
    planck_landing_platform_state->ve = mavlink_msg_planck_landing_platform_state_get_ve(msg);
    planck_landing_platform_state->vd = mavlink_msg_planck_landing_platform_state_get_vd(msg);
    planck_landing_platform_state->roll = mavlink_msg_planck_landing_platform_state_get_roll(msg);
    planck_landing_platform_state->pitch = mavlink_msg_planck_landing_platform_state_get_pitch(msg);
    planck_landing_platform_state->yaw = mavlink_msg_planck_landing_platform_state_get_yaw(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE_LEN? msg->len : MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE_LEN;
        memset(planck_landing_platform_state, 0, MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE_LEN);
    memcpy(planck_landing_platform_state, _MAV_PAYLOAD(msg), len);
#endif
}
