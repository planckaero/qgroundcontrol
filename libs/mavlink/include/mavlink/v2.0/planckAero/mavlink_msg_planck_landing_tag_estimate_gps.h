#pragma once
// MESSAGE PLANCK_LANDING_TAG_ESTIMATE_GPS PACKING

#define MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS 9008

MAVPACKED(
typedef struct __mavlink_planck_landing_tag_estimate_gps_t {
 int32_t lat; /*< [degE7] Latitude deg * 1E7*/
 int32_t lon; /*< [degE7] Longitude deg * 1E7*/
 float alt; /*< [m] Altitude in meters*/
 float vx; /*< [m/s] North velocity*/
 float vy; /*< [m/s] East velocity*/
 float vz; /*< [m/s] Down velocity*/
 uint8_t target_system; /*<  System ID*/
 uint8_t target_component; /*<  Component ID*/
}) mavlink_planck_landing_tag_estimate_gps_t;

#define MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS_LEN 26
#define MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS_MIN_LEN 26
#define MAVLINK_MSG_ID_9008_LEN 26
#define MAVLINK_MSG_ID_9008_MIN_LEN 26

#define MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS_CRC 88
#define MAVLINK_MSG_ID_9008_CRC 88



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_PLANCK_LANDING_TAG_ESTIMATE_GPS { \
    9008, \
    "PLANCK_LANDING_TAG_ESTIMATE_GPS", \
    8, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 24, offsetof(mavlink_planck_landing_tag_estimate_gps_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 25, offsetof(mavlink_planck_landing_tag_estimate_gps_t, target_component) }, \
         { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 0, offsetof(mavlink_planck_landing_tag_estimate_gps_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 4, offsetof(mavlink_planck_landing_tag_estimate_gps_t, lon) }, \
         { "alt", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_planck_landing_tag_estimate_gps_t, alt) }, \
         { "vx", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_planck_landing_tag_estimate_gps_t, vx) }, \
         { "vy", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_planck_landing_tag_estimate_gps_t, vy) }, \
         { "vz", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_planck_landing_tag_estimate_gps_t, vz) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_PLANCK_LANDING_TAG_ESTIMATE_GPS { \
    "PLANCK_LANDING_TAG_ESTIMATE_GPS", \
    8, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 24, offsetof(mavlink_planck_landing_tag_estimate_gps_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 25, offsetof(mavlink_planck_landing_tag_estimate_gps_t, target_component) }, \
         { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 0, offsetof(mavlink_planck_landing_tag_estimate_gps_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 4, offsetof(mavlink_planck_landing_tag_estimate_gps_t, lon) }, \
         { "alt", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_planck_landing_tag_estimate_gps_t, alt) }, \
         { "vx", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_planck_landing_tag_estimate_gps_t, vx) }, \
         { "vy", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_planck_landing_tag_estimate_gps_t, vy) }, \
         { "vz", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_planck_landing_tag_estimate_gps_t, vz) }, \
         } \
}
#endif

/**
 * @brief Pack a planck_landing_tag_estimate_gps message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system  System ID
 * @param target_component  Component ID
 * @param lat [degE7] Latitude deg * 1E7
 * @param lon [degE7] Longitude deg * 1E7
 * @param alt [m] Altitude in meters
 * @param vx [m/s] North velocity
 * @param vy [m/s] East velocity
 * @param vz [m/s] Down velocity
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_planck_landing_tag_estimate_gps_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t target_system, uint8_t target_component, int32_t lat, int32_t lon, float alt, float vx, float vy, float vz)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS_LEN];
    _mav_put_int32_t(buf, 0, lat);
    _mav_put_int32_t(buf, 4, lon);
    _mav_put_float(buf, 8, alt);
    _mav_put_float(buf, 12, vx);
    _mav_put_float(buf, 16, vy);
    _mav_put_float(buf, 20, vz);
    _mav_put_uint8_t(buf, 24, target_system);
    _mav_put_uint8_t(buf, 25, target_component);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS_LEN);
#else
    mavlink_planck_landing_tag_estimate_gps_t packet;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.vx = vx;
    packet.vy = vy;
    packet.vz = vz;
    packet.target_system = target_system;
    packet.target_component = target_component;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS_MIN_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS_CRC);
}

/**
 * @brief Pack a planck_landing_tag_estimate_gps message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system  System ID
 * @param target_component  Component ID
 * @param lat [degE7] Latitude deg * 1E7
 * @param lon [degE7] Longitude deg * 1E7
 * @param alt [m] Altitude in meters
 * @param vx [m/s] North velocity
 * @param vy [m/s] East velocity
 * @param vz [m/s] Down velocity
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_planck_landing_tag_estimate_gps_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t target_system,uint8_t target_component,int32_t lat,int32_t lon,float alt,float vx,float vy,float vz)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS_LEN];
    _mav_put_int32_t(buf, 0, lat);
    _mav_put_int32_t(buf, 4, lon);
    _mav_put_float(buf, 8, alt);
    _mav_put_float(buf, 12, vx);
    _mav_put_float(buf, 16, vy);
    _mav_put_float(buf, 20, vz);
    _mav_put_uint8_t(buf, 24, target_system);
    _mav_put_uint8_t(buf, 25, target_component);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS_LEN);
#else
    mavlink_planck_landing_tag_estimate_gps_t packet;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.vx = vx;
    packet.vy = vy;
    packet.vz = vz;
    packet.target_system = target_system;
    packet.target_component = target_component;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS_MIN_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS_CRC);
}

/**
 * @brief Encode a planck_landing_tag_estimate_gps struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param planck_landing_tag_estimate_gps C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_planck_landing_tag_estimate_gps_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_planck_landing_tag_estimate_gps_t* planck_landing_tag_estimate_gps)
{
    return mavlink_msg_planck_landing_tag_estimate_gps_pack(system_id, component_id, msg, planck_landing_tag_estimate_gps->target_system, planck_landing_tag_estimate_gps->target_component, planck_landing_tag_estimate_gps->lat, planck_landing_tag_estimate_gps->lon, planck_landing_tag_estimate_gps->alt, planck_landing_tag_estimate_gps->vx, planck_landing_tag_estimate_gps->vy, planck_landing_tag_estimate_gps->vz);
}

/**
 * @brief Encode a planck_landing_tag_estimate_gps struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param planck_landing_tag_estimate_gps C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_planck_landing_tag_estimate_gps_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_planck_landing_tag_estimate_gps_t* planck_landing_tag_estimate_gps)
{
    return mavlink_msg_planck_landing_tag_estimate_gps_pack_chan(system_id, component_id, chan, msg, planck_landing_tag_estimate_gps->target_system, planck_landing_tag_estimate_gps->target_component, planck_landing_tag_estimate_gps->lat, planck_landing_tag_estimate_gps->lon, planck_landing_tag_estimate_gps->alt, planck_landing_tag_estimate_gps->vx, planck_landing_tag_estimate_gps->vy, planck_landing_tag_estimate_gps->vz);
}

/**
 * @brief Send a planck_landing_tag_estimate_gps message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system  System ID
 * @param target_component  Component ID
 * @param lat [degE7] Latitude deg * 1E7
 * @param lon [degE7] Longitude deg * 1E7
 * @param alt [m] Altitude in meters
 * @param vx [m/s] North velocity
 * @param vy [m/s] East velocity
 * @param vz [m/s] Down velocity
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_planck_landing_tag_estimate_gps_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, int32_t lat, int32_t lon, float alt, float vx, float vy, float vz)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS_LEN];
    _mav_put_int32_t(buf, 0, lat);
    _mav_put_int32_t(buf, 4, lon);
    _mav_put_float(buf, 8, alt);
    _mav_put_float(buf, 12, vx);
    _mav_put_float(buf, 16, vy);
    _mav_put_float(buf, 20, vz);
    _mav_put_uint8_t(buf, 24, target_system);
    _mav_put_uint8_t(buf, 25, target_component);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS, buf, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS_MIN_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS_CRC);
#else
    mavlink_planck_landing_tag_estimate_gps_t packet;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.vx = vx;
    packet.vy = vy;
    packet.vz = vz;
    packet.target_system = target_system;
    packet.target_component = target_component;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS, (const char *)&packet, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS_MIN_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS_CRC);
#endif
}

/**
 * @brief Send a planck_landing_tag_estimate_gps message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_planck_landing_tag_estimate_gps_send_struct(mavlink_channel_t chan, const mavlink_planck_landing_tag_estimate_gps_t* planck_landing_tag_estimate_gps)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_planck_landing_tag_estimate_gps_send(chan, planck_landing_tag_estimate_gps->target_system, planck_landing_tag_estimate_gps->target_component, planck_landing_tag_estimate_gps->lat, planck_landing_tag_estimate_gps->lon, planck_landing_tag_estimate_gps->alt, planck_landing_tag_estimate_gps->vx, planck_landing_tag_estimate_gps->vy, planck_landing_tag_estimate_gps->vz);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS, (const char *)planck_landing_tag_estimate_gps, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS_MIN_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS_CRC);
#endif
}

#if MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_planck_landing_tag_estimate_gps_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t target_system, uint8_t target_component, int32_t lat, int32_t lon, float alt, float vx, float vy, float vz)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int32_t(buf, 0, lat);
    _mav_put_int32_t(buf, 4, lon);
    _mav_put_float(buf, 8, alt);
    _mav_put_float(buf, 12, vx);
    _mav_put_float(buf, 16, vy);
    _mav_put_float(buf, 20, vz);
    _mav_put_uint8_t(buf, 24, target_system);
    _mav_put_uint8_t(buf, 25, target_component);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS, buf, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS_MIN_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS_CRC);
#else
    mavlink_planck_landing_tag_estimate_gps_t *packet = (mavlink_planck_landing_tag_estimate_gps_t *)msgbuf;
    packet->lat = lat;
    packet->lon = lon;
    packet->alt = alt;
    packet->vx = vx;
    packet->vy = vy;
    packet->vz = vz;
    packet->target_system = target_system;
    packet->target_component = target_component;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS, (const char *)packet, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS_MIN_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS_LEN, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS_CRC);
#endif
}
#endif

#endif

// MESSAGE PLANCK_LANDING_TAG_ESTIMATE_GPS UNPACKING


/**
 * @brief Get field target_system from planck_landing_tag_estimate_gps message
 *
 * @return  System ID
 */
static inline uint8_t mavlink_msg_planck_landing_tag_estimate_gps_get_target_system(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  24);
}

/**
 * @brief Get field target_component from planck_landing_tag_estimate_gps message
 *
 * @return  Component ID
 */
static inline uint8_t mavlink_msg_planck_landing_tag_estimate_gps_get_target_component(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  25);
}

/**
 * @brief Get field lat from planck_landing_tag_estimate_gps message
 *
 * @return [degE7] Latitude deg * 1E7
 */
static inline int32_t mavlink_msg_planck_landing_tag_estimate_gps_get_lat(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  0);
}

/**
 * @brief Get field lon from planck_landing_tag_estimate_gps message
 *
 * @return [degE7] Longitude deg * 1E7
 */
static inline int32_t mavlink_msg_planck_landing_tag_estimate_gps_get_lon(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  4);
}

/**
 * @brief Get field alt from planck_landing_tag_estimate_gps message
 *
 * @return [m] Altitude in meters
 */
static inline float mavlink_msg_planck_landing_tag_estimate_gps_get_alt(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field vx from planck_landing_tag_estimate_gps message
 *
 * @return [m/s] North velocity
 */
static inline float mavlink_msg_planck_landing_tag_estimate_gps_get_vx(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field vy from planck_landing_tag_estimate_gps message
 *
 * @return [m/s] East velocity
 */
static inline float mavlink_msg_planck_landing_tag_estimate_gps_get_vy(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field vz from planck_landing_tag_estimate_gps message
 *
 * @return [m/s] Down velocity
 */
static inline float mavlink_msg_planck_landing_tag_estimate_gps_get_vz(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Decode a planck_landing_tag_estimate_gps message into a struct
 *
 * @param msg The message to decode
 * @param planck_landing_tag_estimate_gps C-struct to decode the message contents into
 */
static inline void mavlink_msg_planck_landing_tag_estimate_gps_decode(const mavlink_message_t* msg, mavlink_planck_landing_tag_estimate_gps_t* planck_landing_tag_estimate_gps)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    planck_landing_tag_estimate_gps->lat = mavlink_msg_planck_landing_tag_estimate_gps_get_lat(msg);
    planck_landing_tag_estimate_gps->lon = mavlink_msg_planck_landing_tag_estimate_gps_get_lon(msg);
    planck_landing_tag_estimate_gps->alt = mavlink_msg_planck_landing_tag_estimate_gps_get_alt(msg);
    planck_landing_tag_estimate_gps->vx = mavlink_msg_planck_landing_tag_estimate_gps_get_vx(msg);
    planck_landing_tag_estimate_gps->vy = mavlink_msg_planck_landing_tag_estimate_gps_get_vy(msg);
    planck_landing_tag_estimate_gps->vz = mavlink_msg_planck_landing_tag_estimate_gps_get_vz(msg);
    planck_landing_tag_estimate_gps->target_system = mavlink_msg_planck_landing_tag_estimate_gps_get_target_system(msg);
    planck_landing_tag_estimate_gps->target_component = mavlink_msg_planck_landing_tag_estimate_gps_get_target_component(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS_LEN? msg->len : MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS_LEN;
        memset(planck_landing_tag_estimate_gps, 0, MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS_LEN);
    memcpy(planck_landing_tag_estimate_gps, _MAV_PAYLOAD(msg), len);
#endif
}
