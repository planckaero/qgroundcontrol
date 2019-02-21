#pragma once
// MESSAGE TARGET_STATE PACKING

#define MAVLINK_MSG_ID_TARGET_STATE 9159

MAVPACKED(
typedef struct __mavlink_target_state_t {
 uint64_t time_usec; /*<  Timestamp (micros since boot or Unix epoch)*/
 uint32_t id; /*<  Target ID (1-based)*/
 int32_t latitude; /*<  Latitude (WGS84), in degrees * 1E7*/
 int32_t longitude; /*<  Longitude (WGS84, in degrees * 1E7*/
 int32_t altitude; /*<  Altitude (AMSL), in meters * 1000 (positive for up)*/
 float vn; /*<  GPS velocity in m/s in NORTH direction in earth-fixed NED frame*/
 float ve; /*<  GPS velocity in m/s in EAST direction in earth-fixed NED frame*/
 float vd; /*<  GPS velocity in m/s in DOWN direction in earth-fixed NED frame*/
 float heading; /*<  Heading in degrees (0=North, positive clockwise)*/
}) mavlink_target_state_t;

#define MAVLINK_MSG_ID_TARGET_STATE_LEN 40
#define MAVLINK_MSG_ID_TARGET_STATE_MIN_LEN 40
#define MAVLINK_MSG_ID_9159_LEN 40
#define MAVLINK_MSG_ID_9159_MIN_LEN 40

#define MAVLINK_MSG_ID_TARGET_STATE_CRC 33
#define MAVLINK_MSG_ID_9159_CRC 33



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_TARGET_STATE { \
    9159, \
    "TARGET_STATE", \
    9, \
    {  { "id", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_target_state_t, id) }, \
         { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_target_state_t, time_usec) }, \
         { "latitude", NULL, MAVLINK_TYPE_INT32_T, 0, 12, offsetof(mavlink_target_state_t, latitude) }, \
         { "longitude", NULL, MAVLINK_TYPE_INT32_T, 0, 16, offsetof(mavlink_target_state_t, longitude) }, \
         { "altitude", NULL, MAVLINK_TYPE_INT32_T, 0, 20, offsetof(mavlink_target_state_t, altitude) }, \
         { "vn", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_target_state_t, vn) }, \
         { "ve", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_target_state_t, ve) }, \
         { "vd", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_target_state_t, vd) }, \
         { "heading", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_target_state_t, heading) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_TARGET_STATE { \
    "TARGET_STATE", \
    9, \
    {  { "id", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_target_state_t, id) }, \
         { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_target_state_t, time_usec) }, \
         { "latitude", NULL, MAVLINK_TYPE_INT32_T, 0, 12, offsetof(mavlink_target_state_t, latitude) }, \
         { "longitude", NULL, MAVLINK_TYPE_INT32_T, 0, 16, offsetof(mavlink_target_state_t, longitude) }, \
         { "altitude", NULL, MAVLINK_TYPE_INT32_T, 0, 20, offsetof(mavlink_target_state_t, altitude) }, \
         { "vn", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_target_state_t, vn) }, \
         { "ve", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_target_state_t, ve) }, \
         { "vd", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_target_state_t, vd) }, \
         { "heading", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_target_state_t, heading) }, \
         } \
}
#endif

/**
 * @brief Pack a target_state message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param id  Target ID (1-based)
 * @param time_usec  Timestamp (micros since boot or Unix epoch)
 * @param latitude  Latitude (WGS84), in degrees * 1E7
 * @param longitude  Longitude (WGS84, in degrees * 1E7
 * @param altitude  Altitude (AMSL), in meters * 1000 (positive for up)
 * @param vn  GPS velocity in m/s in NORTH direction in earth-fixed NED frame
 * @param ve  GPS velocity in m/s in EAST direction in earth-fixed NED frame
 * @param vd  GPS velocity in m/s in DOWN direction in earth-fixed NED frame
 * @param heading  Heading in degrees (0=North, positive clockwise)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_target_state_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t id, uint64_t time_usec, int32_t latitude, int32_t longitude, int32_t altitude, float vn, float ve, float vd, float heading)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TARGET_STATE_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, id);
    _mav_put_int32_t(buf, 12, latitude);
    _mav_put_int32_t(buf, 16, longitude);
    _mav_put_int32_t(buf, 20, altitude);
    _mav_put_float(buf, 24, vn);
    _mav_put_float(buf, 28, ve);
    _mav_put_float(buf, 32, vd);
    _mav_put_float(buf, 36, heading);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TARGET_STATE_LEN);
#else
    mavlink_target_state_t packet;
    packet.time_usec = time_usec;
    packet.id = id;
    packet.latitude = latitude;
    packet.longitude = longitude;
    packet.altitude = altitude;
    packet.vn = vn;
    packet.ve = ve;
    packet.vd = vd;
    packet.heading = heading;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TARGET_STATE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TARGET_STATE;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_TARGET_STATE_MIN_LEN, MAVLINK_MSG_ID_TARGET_STATE_LEN, MAVLINK_MSG_ID_TARGET_STATE_CRC);
}

/**
 * @brief Pack a target_state message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param id  Target ID (1-based)
 * @param time_usec  Timestamp (micros since boot or Unix epoch)
 * @param latitude  Latitude (WGS84), in degrees * 1E7
 * @param longitude  Longitude (WGS84, in degrees * 1E7
 * @param altitude  Altitude (AMSL), in meters * 1000 (positive for up)
 * @param vn  GPS velocity in m/s in NORTH direction in earth-fixed NED frame
 * @param ve  GPS velocity in m/s in EAST direction in earth-fixed NED frame
 * @param vd  GPS velocity in m/s in DOWN direction in earth-fixed NED frame
 * @param heading  Heading in degrees (0=North, positive clockwise)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_target_state_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t id,uint64_t time_usec,int32_t latitude,int32_t longitude,int32_t altitude,float vn,float ve,float vd,float heading)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TARGET_STATE_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, id);
    _mav_put_int32_t(buf, 12, latitude);
    _mav_put_int32_t(buf, 16, longitude);
    _mav_put_int32_t(buf, 20, altitude);
    _mav_put_float(buf, 24, vn);
    _mav_put_float(buf, 28, ve);
    _mav_put_float(buf, 32, vd);
    _mav_put_float(buf, 36, heading);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TARGET_STATE_LEN);
#else
    mavlink_target_state_t packet;
    packet.time_usec = time_usec;
    packet.id = id;
    packet.latitude = latitude;
    packet.longitude = longitude;
    packet.altitude = altitude;
    packet.vn = vn;
    packet.ve = ve;
    packet.vd = vd;
    packet.heading = heading;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TARGET_STATE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TARGET_STATE;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_TARGET_STATE_MIN_LEN, MAVLINK_MSG_ID_TARGET_STATE_LEN, MAVLINK_MSG_ID_TARGET_STATE_CRC);
}

/**
 * @brief Encode a target_state struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param target_state C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_target_state_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_target_state_t* target_state)
{
    return mavlink_msg_target_state_pack(system_id, component_id, msg, target_state->id, target_state->time_usec, target_state->latitude, target_state->longitude, target_state->altitude, target_state->vn, target_state->ve, target_state->vd, target_state->heading);
}

/**
 * @brief Encode a target_state struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_state C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_target_state_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_target_state_t* target_state)
{
    return mavlink_msg_target_state_pack_chan(system_id, component_id, chan, msg, target_state->id, target_state->time_usec, target_state->latitude, target_state->longitude, target_state->altitude, target_state->vn, target_state->ve, target_state->vd, target_state->heading);
}

/**
 * @brief Send a target_state message
 * @param chan MAVLink channel to send the message
 *
 * @param id  Target ID (1-based)
 * @param time_usec  Timestamp (micros since boot or Unix epoch)
 * @param latitude  Latitude (WGS84), in degrees * 1E7
 * @param longitude  Longitude (WGS84, in degrees * 1E7
 * @param altitude  Altitude (AMSL), in meters * 1000 (positive for up)
 * @param vn  GPS velocity in m/s in NORTH direction in earth-fixed NED frame
 * @param ve  GPS velocity in m/s in EAST direction in earth-fixed NED frame
 * @param vd  GPS velocity in m/s in DOWN direction in earth-fixed NED frame
 * @param heading  Heading in degrees (0=North, positive clockwise)
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_target_state_send(mavlink_channel_t chan, uint32_t id, uint64_t time_usec, int32_t latitude, int32_t longitude, int32_t altitude, float vn, float ve, float vd, float heading)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TARGET_STATE_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, id);
    _mav_put_int32_t(buf, 12, latitude);
    _mav_put_int32_t(buf, 16, longitude);
    _mav_put_int32_t(buf, 20, altitude);
    _mav_put_float(buf, 24, vn);
    _mav_put_float(buf, 28, ve);
    _mav_put_float(buf, 32, vd);
    _mav_put_float(buf, 36, heading);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_STATE, buf, MAVLINK_MSG_ID_TARGET_STATE_MIN_LEN, MAVLINK_MSG_ID_TARGET_STATE_LEN, MAVLINK_MSG_ID_TARGET_STATE_CRC);
#else
    mavlink_target_state_t packet;
    packet.time_usec = time_usec;
    packet.id = id;
    packet.latitude = latitude;
    packet.longitude = longitude;
    packet.altitude = altitude;
    packet.vn = vn;
    packet.ve = ve;
    packet.vd = vd;
    packet.heading = heading;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_STATE, (const char *)&packet, MAVLINK_MSG_ID_TARGET_STATE_MIN_LEN, MAVLINK_MSG_ID_TARGET_STATE_LEN, MAVLINK_MSG_ID_TARGET_STATE_CRC);
#endif
}

/**
 * @brief Send a target_state message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_target_state_send_struct(mavlink_channel_t chan, const mavlink_target_state_t* target_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_target_state_send(chan, target_state->id, target_state->time_usec, target_state->latitude, target_state->longitude, target_state->altitude, target_state->vn, target_state->ve, target_state->vd, target_state->heading);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_STATE, (const char *)target_state, MAVLINK_MSG_ID_TARGET_STATE_MIN_LEN, MAVLINK_MSG_ID_TARGET_STATE_LEN, MAVLINK_MSG_ID_TARGET_STATE_CRC);
#endif
}

#if MAVLINK_MSG_ID_TARGET_STATE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_target_state_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t id, uint64_t time_usec, int32_t latitude, int32_t longitude, int32_t altitude, float vn, float ve, float vd, float heading)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint32_t(buf, 8, id);
    _mav_put_int32_t(buf, 12, latitude);
    _mav_put_int32_t(buf, 16, longitude);
    _mav_put_int32_t(buf, 20, altitude);
    _mav_put_float(buf, 24, vn);
    _mav_put_float(buf, 28, ve);
    _mav_put_float(buf, 32, vd);
    _mav_put_float(buf, 36, heading);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_STATE, buf, MAVLINK_MSG_ID_TARGET_STATE_MIN_LEN, MAVLINK_MSG_ID_TARGET_STATE_LEN, MAVLINK_MSG_ID_TARGET_STATE_CRC);
#else
    mavlink_target_state_t *packet = (mavlink_target_state_t *)msgbuf;
    packet->time_usec = time_usec;
    packet->id = id;
    packet->latitude = latitude;
    packet->longitude = longitude;
    packet->altitude = altitude;
    packet->vn = vn;
    packet->ve = ve;
    packet->vd = vd;
    packet->heading = heading;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TARGET_STATE, (const char *)packet, MAVLINK_MSG_ID_TARGET_STATE_MIN_LEN, MAVLINK_MSG_ID_TARGET_STATE_LEN, MAVLINK_MSG_ID_TARGET_STATE_CRC);
#endif
}
#endif

#endif

// MESSAGE TARGET_STATE UNPACKING


/**
 * @brief Get field id from target_state message
 *
 * @return  Target ID (1-based)
 */
static inline uint32_t mavlink_msg_target_state_get_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  8);
}

/**
 * @brief Get field time_usec from target_state message
 *
 * @return  Timestamp (micros since boot or Unix epoch)
 */
static inline uint64_t mavlink_msg_target_state_get_time_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field latitude from target_state message
 *
 * @return  Latitude (WGS84), in degrees * 1E7
 */
static inline int32_t mavlink_msg_target_state_get_latitude(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  12);
}

/**
 * @brief Get field longitude from target_state message
 *
 * @return  Longitude (WGS84, in degrees * 1E7
 */
static inline int32_t mavlink_msg_target_state_get_longitude(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  16);
}

/**
 * @brief Get field altitude from target_state message
 *
 * @return  Altitude (AMSL), in meters * 1000 (positive for up)
 */
static inline int32_t mavlink_msg_target_state_get_altitude(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  20);
}

/**
 * @brief Get field vn from target_state message
 *
 * @return  GPS velocity in m/s in NORTH direction in earth-fixed NED frame
 */
static inline float mavlink_msg_target_state_get_vn(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field ve from target_state message
 *
 * @return  GPS velocity in m/s in EAST direction in earth-fixed NED frame
 */
static inline float mavlink_msg_target_state_get_ve(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field vd from target_state message
 *
 * @return  GPS velocity in m/s in DOWN direction in earth-fixed NED frame
 */
static inline float mavlink_msg_target_state_get_vd(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Get field heading from target_state message
 *
 * @return  Heading in degrees (0=North, positive clockwise)
 */
static inline float mavlink_msg_target_state_get_heading(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  36);
}

/**
 * @brief Decode a target_state message into a struct
 *
 * @param msg The message to decode
 * @param target_state C-struct to decode the message contents into
 */
static inline void mavlink_msg_target_state_decode(const mavlink_message_t* msg, mavlink_target_state_t* target_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    target_state->time_usec = mavlink_msg_target_state_get_time_usec(msg);
    target_state->id = mavlink_msg_target_state_get_id(msg);
    target_state->latitude = mavlink_msg_target_state_get_latitude(msg);
    target_state->longitude = mavlink_msg_target_state_get_longitude(msg);
    target_state->altitude = mavlink_msg_target_state_get_altitude(msg);
    target_state->vn = mavlink_msg_target_state_get_vn(msg);
    target_state->ve = mavlink_msg_target_state_get_ve(msg);
    target_state->vd = mavlink_msg_target_state_get_vd(msg);
    target_state->heading = mavlink_msg_target_state_get_heading(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_TARGET_STATE_LEN? msg->len : MAVLINK_MSG_ID_TARGET_STATE_LEN;
        memset(target_state, 0, MAVLINK_MSG_ID_TARGET_STATE_LEN);
    memcpy(target_state, _MAV_PAYLOAD(msg), len);
#endif
}
