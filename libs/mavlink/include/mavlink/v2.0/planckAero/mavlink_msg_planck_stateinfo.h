#pragma once
// MESSAGE PLANCK_STATEINFO PACKING

#define MAVLINK_MSG_ID_PLANCK_STATEINFO 9001

MAVPACKED(
typedef struct __mavlink_planck_stateinfo_t {
 uint64_t time_usec; /*< [us] Timestamp (micros since boot)*/
 uint64_t time_unix_usec; /*< [us] Timestamp of the master clock in microseconds since UNIX epoch*/
 float roll; /*< [rad] Roll angle (rad, -pi..+pi)*/
 float pitch; /*< [rad] Pitch angle (rad, -pi..+pi)*/
 float yaw; /*< [rad] Yaw angle (rad, -pi..+pi)*/
 float gyro_x; /*< [rad/s] X-axis gyro rate*/
 float gyro_y; /*< [rad/s] Y-axis gyro rate*/
 float gyro_z; /*< [rad/s] Z-axis gyro rate*/
 float xacc; /*< [m/s/s] X acceleration (raw)*/
 float yacc; /*< [m/s/s] Y acceleration (raw)*/
 float zacc; /*< [m/s/s] Z acceleration (raw)*/
 int32_t lat; /*< [degE7] Latitude*/
 int32_t lon; /*< [degE7] Longitude*/
 int32_t alt; /*< [mm] Altitude, expressed as * 1000 (millimeters), AMSL (not WGS84 - note that virtually all GPS modules provide the AMSL as well)*/
 int32_t relative_alt; /*< [mm] Altitude above home in meters, expressed as * 1000 (millimeters)*/
 int32_t alt_above_terrain; /*< [mm] Altitude above terrain in meters, expressed as * 1000 (millimeters)*/
 float vn; /*< [m/s] GPS velocity in m/s in NORTH direction in earth-fixed NED frame*/
 float ve; /*< [m/s] GPS velocity in m/s in EAST direction in earth-fixed NED frame*/
 float vd; /*< [m/s] GPS velocity in m/s in DOWN direction in earth-fixed NED frame*/
 uint8_t target_system; /*<  System ID*/
 uint8_t target_component; /*<  Component ID*/
 uint8_t mode; /*<  Current flight mode*/
 uint8_t status; /*<  Flight status: bit0:armed, bit1:in_flight, bit2:failsafe*/
}) mavlink_planck_stateinfo_t;

#define MAVLINK_MSG_ID_PLANCK_STATEINFO_LEN 88
#define MAVLINK_MSG_ID_PLANCK_STATEINFO_MIN_LEN 88
#define MAVLINK_MSG_ID_9001_LEN 88
#define MAVLINK_MSG_ID_9001_MIN_LEN 88

#define MAVLINK_MSG_ID_PLANCK_STATEINFO_CRC 203
#define MAVLINK_MSG_ID_9001_CRC 203



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_PLANCK_STATEINFO { \
    9001, \
    "PLANCK_STATEINFO", \
    23, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 84, offsetof(mavlink_planck_stateinfo_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 85, offsetof(mavlink_planck_stateinfo_t, target_component) }, \
         { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_planck_stateinfo_t, time_usec) }, \
         { "time_unix_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_planck_stateinfo_t, time_unix_usec) }, \
         { "mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 86, offsetof(mavlink_planck_stateinfo_t, mode) }, \
         { "status", NULL, MAVLINK_TYPE_UINT8_T, 0, 87, offsetof(mavlink_planck_stateinfo_t, status) }, \
         { "roll", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_planck_stateinfo_t, roll) }, \
         { "pitch", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_planck_stateinfo_t, pitch) }, \
         { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_planck_stateinfo_t, yaw) }, \
         { "gyro_x", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_planck_stateinfo_t, gyro_x) }, \
         { "gyro_y", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_planck_stateinfo_t, gyro_y) }, \
         { "gyro_z", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_planck_stateinfo_t, gyro_z) }, \
         { "xacc", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_planck_stateinfo_t, xacc) }, \
         { "yacc", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_planck_stateinfo_t, yacc) }, \
         { "zacc", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_planck_stateinfo_t, zacc) }, \
         { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 52, offsetof(mavlink_planck_stateinfo_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 56, offsetof(mavlink_planck_stateinfo_t, lon) }, \
         { "alt", NULL, MAVLINK_TYPE_INT32_T, 0, 60, offsetof(mavlink_planck_stateinfo_t, alt) }, \
         { "relative_alt", NULL, MAVLINK_TYPE_INT32_T, 0, 64, offsetof(mavlink_planck_stateinfo_t, relative_alt) }, \
         { "alt_above_terrain", NULL, MAVLINK_TYPE_INT32_T, 0, 68, offsetof(mavlink_planck_stateinfo_t, alt_above_terrain) }, \
         { "vn", NULL, MAVLINK_TYPE_FLOAT, 0, 72, offsetof(mavlink_planck_stateinfo_t, vn) }, \
         { "ve", NULL, MAVLINK_TYPE_FLOAT, 0, 76, offsetof(mavlink_planck_stateinfo_t, ve) }, \
         { "vd", NULL, MAVLINK_TYPE_FLOAT, 0, 80, offsetof(mavlink_planck_stateinfo_t, vd) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_PLANCK_STATEINFO { \
    "PLANCK_STATEINFO", \
    23, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 84, offsetof(mavlink_planck_stateinfo_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 85, offsetof(mavlink_planck_stateinfo_t, target_component) }, \
         { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_planck_stateinfo_t, time_usec) }, \
         { "time_unix_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_planck_stateinfo_t, time_unix_usec) }, \
         { "mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 86, offsetof(mavlink_planck_stateinfo_t, mode) }, \
         { "status", NULL, MAVLINK_TYPE_UINT8_T, 0, 87, offsetof(mavlink_planck_stateinfo_t, status) }, \
         { "roll", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_planck_stateinfo_t, roll) }, \
         { "pitch", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_planck_stateinfo_t, pitch) }, \
         { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_planck_stateinfo_t, yaw) }, \
         { "gyro_x", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_planck_stateinfo_t, gyro_x) }, \
         { "gyro_y", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_planck_stateinfo_t, gyro_y) }, \
         { "gyro_z", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_planck_stateinfo_t, gyro_z) }, \
         { "xacc", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_planck_stateinfo_t, xacc) }, \
         { "yacc", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_planck_stateinfo_t, yacc) }, \
         { "zacc", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_planck_stateinfo_t, zacc) }, \
         { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 52, offsetof(mavlink_planck_stateinfo_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 56, offsetof(mavlink_planck_stateinfo_t, lon) }, \
         { "alt", NULL, MAVLINK_TYPE_INT32_T, 0, 60, offsetof(mavlink_planck_stateinfo_t, alt) }, \
         { "relative_alt", NULL, MAVLINK_TYPE_INT32_T, 0, 64, offsetof(mavlink_planck_stateinfo_t, relative_alt) }, \
         { "alt_above_terrain", NULL, MAVLINK_TYPE_INT32_T, 0, 68, offsetof(mavlink_planck_stateinfo_t, alt_above_terrain) }, \
         { "vn", NULL, MAVLINK_TYPE_FLOAT, 0, 72, offsetof(mavlink_planck_stateinfo_t, vn) }, \
         { "ve", NULL, MAVLINK_TYPE_FLOAT, 0, 76, offsetof(mavlink_planck_stateinfo_t, ve) }, \
         { "vd", NULL, MAVLINK_TYPE_FLOAT, 0, 80, offsetof(mavlink_planck_stateinfo_t, vd) }, \
         } \
}
#endif

/**
 * @brief Pack a planck_stateinfo message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system  System ID
 * @param target_component  Component ID
 * @param time_usec [us] Timestamp (micros since boot)
 * @param time_unix_usec [us] Timestamp of the master clock in microseconds since UNIX epoch
 * @param mode  Current flight mode
 * @param status  Flight status: bit0:armed, bit1:in_flight, bit2:failsafe
 * @param roll [rad] Roll angle (rad, -pi..+pi)
 * @param pitch [rad] Pitch angle (rad, -pi..+pi)
 * @param yaw [rad] Yaw angle (rad, -pi..+pi)
 * @param gyro_x [rad/s] X-axis gyro rate
 * @param gyro_y [rad/s] Y-axis gyro rate
 * @param gyro_z [rad/s] Z-axis gyro rate
 * @param xacc [m/s/s] X acceleration (raw)
 * @param yacc [m/s/s] Y acceleration (raw)
 * @param zacc [m/s/s] Z acceleration (raw)
 * @param lat [degE7] Latitude
 * @param lon [degE7] Longitude
 * @param alt [mm] Altitude, expressed as * 1000 (millimeters), AMSL (not WGS84 - note that virtually all GPS modules provide the AMSL as well)
 * @param relative_alt [mm] Altitude above home in meters, expressed as * 1000 (millimeters)
 * @param alt_above_terrain [mm] Altitude above terrain in meters, expressed as * 1000 (millimeters)
 * @param vn [m/s] GPS velocity in m/s in NORTH direction in earth-fixed NED frame
 * @param ve [m/s] GPS velocity in m/s in EAST direction in earth-fixed NED frame
 * @param vd [m/s] GPS velocity in m/s in DOWN direction in earth-fixed NED frame
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_planck_stateinfo_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t target_system, uint8_t target_component, uint64_t time_usec, uint64_t time_unix_usec, uint8_t mode, uint8_t status, float roll, float pitch, float yaw, float gyro_x, float gyro_y, float gyro_z, float xacc, float yacc, float zacc, int32_t lat, int32_t lon, int32_t alt, int32_t relative_alt, int32_t alt_above_terrain, float vn, float ve, float vd)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLANCK_STATEINFO_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint64_t(buf, 8, time_unix_usec);
    _mav_put_float(buf, 16, roll);
    _mav_put_float(buf, 20, pitch);
    _mav_put_float(buf, 24, yaw);
    _mav_put_float(buf, 28, gyro_x);
    _mav_put_float(buf, 32, gyro_y);
    _mav_put_float(buf, 36, gyro_z);
    _mav_put_float(buf, 40, xacc);
    _mav_put_float(buf, 44, yacc);
    _mav_put_float(buf, 48, zacc);
    _mav_put_int32_t(buf, 52, lat);
    _mav_put_int32_t(buf, 56, lon);
    _mav_put_int32_t(buf, 60, alt);
    _mav_put_int32_t(buf, 64, relative_alt);
    _mav_put_int32_t(buf, 68, alt_above_terrain);
    _mav_put_float(buf, 72, vn);
    _mav_put_float(buf, 76, ve);
    _mav_put_float(buf, 80, vd);
    _mav_put_uint8_t(buf, 84, target_system);
    _mav_put_uint8_t(buf, 85, target_component);
    _mav_put_uint8_t(buf, 86, mode);
    _mav_put_uint8_t(buf, 87, status);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PLANCK_STATEINFO_LEN);
#else
    mavlink_planck_stateinfo_t packet;
    packet.time_usec = time_usec;
    packet.time_unix_usec = time_unix_usec;
    packet.roll = roll;
    packet.pitch = pitch;
    packet.yaw = yaw;
    packet.gyro_x = gyro_x;
    packet.gyro_y = gyro_y;
    packet.gyro_z = gyro_z;
    packet.xacc = xacc;
    packet.yacc = yacc;
    packet.zacc = zacc;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.relative_alt = relative_alt;
    packet.alt_above_terrain = alt_above_terrain;
    packet.vn = vn;
    packet.ve = ve;
    packet.vd = vd;
    packet.target_system = target_system;
    packet.target_component = target_component;
    packet.mode = mode;
    packet.status = status;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PLANCK_STATEINFO_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PLANCK_STATEINFO;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_PLANCK_STATEINFO_MIN_LEN, MAVLINK_MSG_ID_PLANCK_STATEINFO_LEN, MAVLINK_MSG_ID_PLANCK_STATEINFO_CRC);
}

/**
 * @brief Pack a planck_stateinfo message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system  System ID
 * @param target_component  Component ID
 * @param time_usec [us] Timestamp (micros since boot)
 * @param time_unix_usec [us] Timestamp of the master clock in microseconds since UNIX epoch
 * @param mode  Current flight mode
 * @param status  Flight status: bit0:armed, bit1:in_flight, bit2:failsafe
 * @param roll [rad] Roll angle (rad, -pi..+pi)
 * @param pitch [rad] Pitch angle (rad, -pi..+pi)
 * @param yaw [rad] Yaw angle (rad, -pi..+pi)
 * @param gyro_x [rad/s] X-axis gyro rate
 * @param gyro_y [rad/s] Y-axis gyro rate
 * @param gyro_z [rad/s] Z-axis gyro rate
 * @param xacc [m/s/s] X acceleration (raw)
 * @param yacc [m/s/s] Y acceleration (raw)
 * @param zacc [m/s/s] Z acceleration (raw)
 * @param lat [degE7] Latitude
 * @param lon [degE7] Longitude
 * @param alt [mm] Altitude, expressed as * 1000 (millimeters), AMSL (not WGS84 - note that virtually all GPS modules provide the AMSL as well)
 * @param relative_alt [mm] Altitude above home in meters, expressed as * 1000 (millimeters)
 * @param alt_above_terrain [mm] Altitude above terrain in meters, expressed as * 1000 (millimeters)
 * @param vn [m/s] GPS velocity in m/s in NORTH direction in earth-fixed NED frame
 * @param ve [m/s] GPS velocity in m/s in EAST direction in earth-fixed NED frame
 * @param vd [m/s] GPS velocity in m/s in DOWN direction in earth-fixed NED frame
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_planck_stateinfo_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t target_system,uint8_t target_component,uint64_t time_usec,uint64_t time_unix_usec,uint8_t mode,uint8_t status,float roll,float pitch,float yaw,float gyro_x,float gyro_y,float gyro_z,float xacc,float yacc,float zacc,int32_t lat,int32_t lon,int32_t alt,int32_t relative_alt,int32_t alt_above_terrain,float vn,float ve,float vd)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLANCK_STATEINFO_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint64_t(buf, 8, time_unix_usec);
    _mav_put_float(buf, 16, roll);
    _mav_put_float(buf, 20, pitch);
    _mav_put_float(buf, 24, yaw);
    _mav_put_float(buf, 28, gyro_x);
    _mav_put_float(buf, 32, gyro_y);
    _mav_put_float(buf, 36, gyro_z);
    _mav_put_float(buf, 40, xacc);
    _mav_put_float(buf, 44, yacc);
    _mav_put_float(buf, 48, zacc);
    _mav_put_int32_t(buf, 52, lat);
    _mav_put_int32_t(buf, 56, lon);
    _mav_put_int32_t(buf, 60, alt);
    _mav_put_int32_t(buf, 64, relative_alt);
    _mav_put_int32_t(buf, 68, alt_above_terrain);
    _mav_put_float(buf, 72, vn);
    _mav_put_float(buf, 76, ve);
    _mav_put_float(buf, 80, vd);
    _mav_put_uint8_t(buf, 84, target_system);
    _mav_put_uint8_t(buf, 85, target_component);
    _mav_put_uint8_t(buf, 86, mode);
    _mav_put_uint8_t(buf, 87, status);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PLANCK_STATEINFO_LEN);
#else
    mavlink_planck_stateinfo_t packet;
    packet.time_usec = time_usec;
    packet.time_unix_usec = time_unix_usec;
    packet.roll = roll;
    packet.pitch = pitch;
    packet.yaw = yaw;
    packet.gyro_x = gyro_x;
    packet.gyro_y = gyro_y;
    packet.gyro_z = gyro_z;
    packet.xacc = xacc;
    packet.yacc = yacc;
    packet.zacc = zacc;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.relative_alt = relative_alt;
    packet.alt_above_terrain = alt_above_terrain;
    packet.vn = vn;
    packet.ve = ve;
    packet.vd = vd;
    packet.target_system = target_system;
    packet.target_component = target_component;
    packet.mode = mode;
    packet.status = status;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PLANCK_STATEINFO_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PLANCK_STATEINFO;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_PLANCK_STATEINFO_MIN_LEN, MAVLINK_MSG_ID_PLANCK_STATEINFO_LEN, MAVLINK_MSG_ID_PLANCK_STATEINFO_CRC);
}

/**
 * @brief Encode a planck_stateinfo struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param planck_stateinfo C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_planck_stateinfo_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_planck_stateinfo_t* planck_stateinfo)
{
    return mavlink_msg_planck_stateinfo_pack(system_id, component_id, msg, planck_stateinfo->target_system, planck_stateinfo->target_component, planck_stateinfo->time_usec, planck_stateinfo->time_unix_usec, planck_stateinfo->mode, planck_stateinfo->status, planck_stateinfo->roll, planck_stateinfo->pitch, planck_stateinfo->yaw, planck_stateinfo->gyro_x, planck_stateinfo->gyro_y, planck_stateinfo->gyro_z, planck_stateinfo->xacc, planck_stateinfo->yacc, planck_stateinfo->zacc, planck_stateinfo->lat, planck_stateinfo->lon, planck_stateinfo->alt, planck_stateinfo->relative_alt, planck_stateinfo->alt_above_terrain, planck_stateinfo->vn, planck_stateinfo->ve, planck_stateinfo->vd);
}

/**
 * @brief Encode a planck_stateinfo struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param planck_stateinfo C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_planck_stateinfo_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_planck_stateinfo_t* planck_stateinfo)
{
    return mavlink_msg_planck_stateinfo_pack_chan(system_id, component_id, chan, msg, planck_stateinfo->target_system, planck_stateinfo->target_component, planck_stateinfo->time_usec, planck_stateinfo->time_unix_usec, planck_stateinfo->mode, planck_stateinfo->status, planck_stateinfo->roll, planck_stateinfo->pitch, planck_stateinfo->yaw, planck_stateinfo->gyro_x, planck_stateinfo->gyro_y, planck_stateinfo->gyro_z, planck_stateinfo->xacc, planck_stateinfo->yacc, planck_stateinfo->zacc, planck_stateinfo->lat, planck_stateinfo->lon, planck_stateinfo->alt, planck_stateinfo->relative_alt, planck_stateinfo->alt_above_terrain, planck_stateinfo->vn, planck_stateinfo->ve, planck_stateinfo->vd);
}

/**
 * @brief Send a planck_stateinfo message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system  System ID
 * @param target_component  Component ID
 * @param time_usec [us] Timestamp (micros since boot)
 * @param time_unix_usec [us] Timestamp of the master clock in microseconds since UNIX epoch
 * @param mode  Current flight mode
 * @param status  Flight status: bit0:armed, bit1:in_flight, bit2:failsafe
 * @param roll [rad] Roll angle (rad, -pi..+pi)
 * @param pitch [rad] Pitch angle (rad, -pi..+pi)
 * @param yaw [rad] Yaw angle (rad, -pi..+pi)
 * @param gyro_x [rad/s] X-axis gyro rate
 * @param gyro_y [rad/s] Y-axis gyro rate
 * @param gyro_z [rad/s] Z-axis gyro rate
 * @param xacc [m/s/s] X acceleration (raw)
 * @param yacc [m/s/s] Y acceleration (raw)
 * @param zacc [m/s/s] Z acceleration (raw)
 * @param lat [degE7] Latitude
 * @param lon [degE7] Longitude
 * @param alt [mm] Altitude, expressed as * 1000 (millimeters), AMSL (not WGS84 - note that virtually all GPS modules provide the AMSL as well)
 * @param relative_alt [mm] Altitude above home in meters, expressed as * 1000 (millimeters)
 * @param alt_above_terrain [mm] Altitude above terrain in meters, expressed as * 1000 (millimeters)
 * @param vn [m/s] GPS velocity in m/s in NORTH direction in earth-fixed NED frame
 * @param ve [m/s] GPS velocity in m/s in EAST direction in earth-fixed NED frame
 * @param vd [m/s] GPS velocity in m/s in DOWN direction in earth-fixed NED frame
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_planck_stateinfo_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, uint64_t time_usec, uint64_t time_unix_usec, uint8_t mode, uint8_t status, float roll, float pitch, float yaw, float gyro_x, float gyro_y, float gyro_z, float xacc, float yacc, float zacc, int32_t lat, int32_t lon, int32_t alt, int32_t relative_alt, int32_t alt_above_terrain, float vn, float ve, float vd)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLANCK_STATEINFO_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint64_t(buf, 8, time_unix_usec);
    _mav_put_float(buf, 16, roll);
    _mav_put_float(buf, 20, pitch);
    _mav_put_float(buf, 24, yaw);
    _mav_put_float(buf, 28, gyro_x);
    _mav_put_float(buf, 32, gyro_y);
    _mav_put_float(buf, 36, gyro_z);
    _mav_put_float(buf, 40, xacc);
    _mav_put_float(buf, 44, yacc);
    _mav_put_float(buf, 48, zacc);
    _mav_put_int32_t(buf, 52, lat);
    _mav_put_int32_t(buf, 56, lon);
    _mav_put_int32_t(buf, 60, alt);
    _mav_put_int32_t(buf, 64, relative_alt);
    _mav_put_int32_t(buf, 68, alt_above_terrain);
    _mav_put_float(buf, 72, vn);
    _mav_put_float(buf, 76, ve);
    _mav_put_float(buf, 80, vd);
    _mav_put_uint8_t(buf, 84, target_system);
    _mav_put_uint8_t(buf, 85, target_component);
    _mav_put_uint8_t(buf, 86, mode);
    _mav_put_uint8_t(buf, 87, status);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_STATEINFO, buf, MAVLINK_MSG_ID_PLANCK_STATEINFO_MIN_LEN, MAVLINK_MSG_ID_PLANCK_STATEINFO_LEN, MAVLINK_MSG_ID_PLANCK_STATEINFO_CRC);
#else
    mavlink_planck_stateinfo_t packet;
    packet.time_usec = time_usec;
    packet.time_unix_usec = time_unix_usec;
    packet.roll = roll;
    packet.pitch = pitch;
    packet.yaw = yaw;
    packet.gyro_x = gyro_x;
    packet.gyro_y = gyro_y;
    packet.gyro_z = gyro_z;
    packet.xacc = xacc;
    packet.yacc = yacc;
    packet.zacc = zacc;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.relative_alt = relative_alt;
    packet.alt_above_terrain = alt_above_terrain;
    packet.vn = vn;
    packet.ve = ve;
    packet.vd = vd;
    packet.target_system = target_system;
    packet.target_component = target_component;
    packet.mode = mode;
    packet.status = status;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_STATEINFO, (const char *)&packet, MAVLINK_MSG_ID_PLANCK_STATEINFO_MIN_LEN, MAVLINK_MSG_ID_PLANCK_STATEINFO_LEN, MAVLINK_MSG_ID_PLANCK_STATEINFO_CRC);
#endif
}

/**
 * @brief Send a planck_stateinfo message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_planck_stateinfo_send_struct(mavlink_channel_t chan, const mavlink_planck_stateinfo_t* planck_stateinfo)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_planck_stateinfo_send(chan, planck_stateinfo->target_system, planck_stateinfo->target_component, planck_stateinfo->time_usec, planck_stateinfo->time_unix_usec, planck_stateinfo->mode, planck_stateinfo->status, planck_stateinfo->roll, planck_stateinfo->pitch, planck_stateinfo->yaw, planck_stateinfo->gyro_x, planck_stateinfo->gyro_y, planck_stateinfo->gyro_z, planck_stateinfo->xacc, planck_stateinfo->yacc, planck_stateinfo->zacc, planck_stateinfo->lat, planck_stateinfo->lon, planck_stateinfo->alt, planck_stateinfo->relative_alt, planck_stateinfo->alt_above_terrain, planck_stateinfo->vn, planck_stateinfo->ve, planck_stateinfo->vd);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_STATEINFO, (const char *)planck_stateinfo, MAVLINK_MSG_ID_PLANCK_STATEINFO_MIN_LEN, MAVLINK_MSG_ID_PLANCK_STATEINFO_LEN, MAVLINK_MSG_ID_PLANCK_STATEINFO_CRC);
#endif
}

#if MAVLINK_MSG_ID_PLANCK_STATEINFO_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_planck_stateinfo_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t target_system, uint8_t target_component, uint64_t time_usec, uint64_t time_unix_usec, uint8_t mode, uint8_t status, float roll, float pitch, float yaw, float gyro_x, float gyro_y, float gyro_z, float xacc, float yacc, float zacc, int32_t lat, int32_t lon, int32_t alt, int32_t relative_alt, int32_t alt_above_terrain, float vn, float ve, float vd)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_uint64_t(buf, 8, time_unix_usec);
    _mav_put_float(buf, 16, roll);
    _mav_put_float(buf, 20, pitch);
    _mav_put_float(buf, 24, yaw);
    _mav_put_float(buf, 28, gyro_x);
    _mav_put_float(buf, 32, gyro_y);
    _mav_put_float(buf, 36, gyro_z);
    _mav_put_float(buf, 40, xacc);
    _mav_put_float(buf, 44, yacc);
    _mav_put_float(buf, 48, zacc);
    _mav_put_int32_t(buf, 52, lat);
    _mav_put_int32_t(buf, 56, lon);
    _mav_put_int32_t(buf, 60, alt);
    _mav_put_int32_t(buf, 64, relative_alt);
    _mav_put_int32_t(buf, 68, alt_above_terrain);
    _mav_put_float(buf, 72, vn);
    _mav_put_float(buf, 76, ve);
    _mav_put_float(buf, 80, vd);
    _mav_put_uint8_t(buf, 84, target_system);
    _mav_put_uint8_t(buf, 85, target_component);
    _mav_put_uint8_t(buf, 86, mode);
    _mav_put_uint8_t(buf, 87, status);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_STATEINFO, buf, MAVLINK_MSG_ID_PLANCK_STATEINFO_MIN_LEN, MAVLINK_MSG_ID_PLANCK_STATEINFO_LEN, MAVLINK_MSG_ID_PLANCK_STATEINFO_CRC);
#else
    mavlink_planck_stateinfo_t *packet = (mavlink_planck_stateinfo_t *)msgbuf;
    packet->time_usec = time_usec;
    packet->time_unix_usec = time_unix_usec;
    packet->roll = roll;
    packet->pitch = pitch;
    packet->yaw = yaw;
    packet->gyro_x = gyro_x;
    packet->gyro_y = gyro_y;
    packet->gyro_z = gyro_z;
    packet->xacc = xacc;
    packet->yacc = yacc;
    packet->zacc = zacc;
    packet->lat = lat;
    packet->lon = lon;
    packet->alt = alt;
    packet->relative_alt = relative_alt;
    packet->alt_above_terrain = alt_above_terrain;
    packet->vn = vn;
    packet->ve = ve;
    packet->vd = vd;
    packet->target_system = target_system;
    packet->target_component = target_component;
    packet->mode = mode;
    packet->status = status;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_STATEINFO, (const char *)packet, MAVLINK_MSG_ID_PLANCK_STATEINFO_MIN_LEN, MAVLINK_MSG_ID_PLANCK_STATEINFO_LEN, MAVLINK_MSG_ID_PLANCK_STATEINFO_CRC);
#endif
}
#endif

#endif

// MESSAGE PLANCK_STATEINFO UNPACKING


/**
 * @brief Get field target_system from planck_stateinfo message
 *
 * @return  System ID
 */
static inline uint8_t mavlink_msg_planck_stateinfo_get_target_system(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  84);
}

/**
 * @brief Get field target_component from planck_stateinfo message
 *
 * @return  Component ID
 */
static inline uint8_t mavlink_msg_planck_stateinfo_get_target_component(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  85);
}

/**
 * @brief Get field time_usec from planck_stateinfo message
 *
 * @return [us] Timestamp (micros since boot)
 */
static inline uint64_t mavlink_msg_planck_stateinfo_get_time_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field time_unix_usec from planck_stateinfo message
 *
 * @return [us] Timestamp of the master clock in microseconds since UNIX epoch
 */
static inline uint64_t mavlink_msg_planck_stateinfo_get_time_unix_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  8);
}

/**
 * @brief Get field mode from planck_stateinfo message
 *
 * @return  Current flight mode
 */
static inline uint8_t mavlink_msg_planck_stateinfo_get_mode(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  86);
}

/**
 * @brief Get field status from planck_stateinfo message
 *
 * @return  Flight status: bit0:armed, bit1:in_flight, bit2:failsafe
 */
static inline uint8_t mavlink_msg_planck_stateinfo_get_status(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  87);
}

/**
 * @brief Get field roll from planck_stateinfo message
 *
 * @return [rad] Roll angle (rad, -pi..+pi)
 */
static inline float mavlink_msg_planck_stateinfo_get_roll(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field pitch from planck_stateinfo message
 *
 * @return [rad] Pitch angle (rad, -pi..+pi)
 */
static inline float mavlink_msg_planck_stateinfo_get_pitch(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field yaw from planck_stateinfo message
 *
 * @return [rad] Yaw angle (rad, -pi..+pi)
 */
static inline float mavlink_msg_planck_stateinfo_get_yaw(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field gyro_x from planck_stateinfo message
 *
 * @return [rad/s] X-axis gyro rate
 */
static inline float mavlink_msg_planck_stateinfo_get_gyro_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field gyro_y from planck_stateinfo message
 *
 * @return [rad/s] Y-axis gyro rate
 */
static inline float mavlink_msg_planck_stateinfo_get_gyro_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Get field gyro_z from planck_stateinfo message
 *
 * @return [rad/s] Z-axis gyro rate
 */
static inline float mavlink_msg_planck_stateinfo_get_gyro_z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  36);
}

/**
 * @brief Get field xacc from planck_stateinfo message
 *
 * @return [m/s/s] X acceleration (raw)
 */
static inline float mavlink_msg_planck_stateinfo_get_xacc(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  40);
}

/**
 * @brief Get field yacc from planck_stateinfo message
 *
 * @return [m/s/s] Y acceleration (raw)
 */
static inline float mavlink_msg_planck_stateinfo_get_yacc(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  44);
}

/**
 * @brief Get field zacc from planck_stateinfo message
 *
 * @return [m/s/s] Z acceleration (raw)
 */
static inline float mavlink_msg_planck_stateinfo_get_zacc(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  48);
}

/**
 * @brief Get field lat from planck_stateinfo message
 *
 * @return [degE7] Latitude
 */
static inline int32_t mavlink_msg_planck_stateinfo_get_lat(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  52);
}

/**
 * @brief Get field lon from planck_stateinfo message
 *
 * @return [degE7] Longitude
 */
static inline int32_t mavlink_msg_planck_stateinfo_get_lon(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  56);
}

/**
 * @brief Get field alt from planck_stateinfo message
 *
 * @return [mm] Altitude, expressed as * 1000 (millimeters), AMSL (not WGS84 - note that virtually all GPS modules provide the AMSL as well)
 */
static inline int32_t mavlink_msg_planck_stateinfo_get_alt(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  60);
}

/**
 * @brief Get field relative_alt from planck_stateinfo message
 *
 * @return [mm] Altitude above home in meters, expressed as * 1000 (millimeters)
 */
static inline int32_t mavlink_msg_planck_stateinfo_get_relative_alt(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  64);
}

/**
 * @brief Get field alt_above_terrain from planck_stateinfo message
 *
 * @return [mm] Altitude above terrain in meters, expressed as * 1000 (millimeters)
 */
static inline int32_t mavlink_msg_planck_stateinfo_get_alt_above_terrain(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  68);
}

/**
 * @brief Get field vn from planck_stateinfo message
 *
 * @return [m/s] GPS velocity in m/s in NORTH direction in earth-fixed NED frame
 */
static inline float mavlink_msg_planck_stateinfo_get_vn(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  72);
}

/**
 * @brief Get field ve from planck_stateinfo message
 *
 * @return [m/s] GPS velocity in m/s in EAST direction in earth-fixed NED frame
 */
static inline float mavlink_msg_planck_stateinfo_get_ve(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  76);
}

/**
 * @brief Get field vd from planck_stateinfo message
 *
 * @return [m/s] GPS velocity in m/s in DOWN direction in earth-fixed NED frame
 */
static inline float mavlink_msg_planck_stateinfo_get_vd(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  80);
}

/**
 * @brief Decode a planck_stateinfo message into a struct
 *
 * @param msg The message to decode
 * @param planck_stateinfo C-struct to decode the message contents into
 */
static inline void mavlink_msg_planck_stateinfo_decode(const mavlink_message_t* msg, mavlink_planck_stateinfo_t* planck_stateinfo)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    planck_stateinfo->time_usec = mavlink_msg_planck_stateinfo_get_time_usec(msg);
    planck_stateinfo->time_unix_usec = mavlink_msg_planck_stateinfo_get_time_unix_usec(msg);
    planck_stateinfo->roll = mavlink_msg_planck_stateinfo_get_roll(msg);
    planck_stateinfo->pitch = mavlink_msg_planck_stateinfo_get_pitch(msg);
    planck_stateinfo->yaw = mavlink_msg_planck_stateinfo_get_yaw(msg);
    planck_stateinfo->gyro_x = mavlink_msg_planck_stateinfo_get_gyro_x(msg);
    planck_stateinfo->gyro_y = mavlink_msg_planck_stateinfo_get_gyro_y(msg);
    planck_stateinfo->gyro_z = mavlink_msg_planck_stateinfo_get_gyro_z(msg);
    planck_stateinfo->xacc = mavlink_msg_planck_stateinfo_get_xacc(msg);
    planck_stateinfo->yacc = mavlink_msg_planck_stateinfo_get_yacc(msg);
    planck_stateinfo->zacc = mavlink_msg_planck_stateinfo_get_zacc(msg);
    planck_stateinfo->lat = mavlink_msg_planck_stateinfo_get_lat(msg);
    planck_stateinfo->lon = mavlink_msg_planck_stateinfo_get_lon(msg);
    planck_stateinfo->alt = mavlink_msg_planck_stateinfo_get_alt(msg);
    planck_stateinfo->relative_alt = mavlink_msg_planck_stateinfo_get_relative_alt(msg);
    planck_stateinfo->alt_above_terrain = mavlink_msg_planck_stateinfo_get_alt_above_terrain(msg);
    planck_stateinfo->vn = mavlink_msg_planck_stateinfo_get_vn(msg);
    planck_stateinfo->ve = mavlink_msg_planck_stateinfo_get_ve(msg);
    planck_stateinfo->vd = mavlink_msg_planck_stateinfo_get_vd(msg);
    planck_stateinfo->target_system = mavlink_msg_planck_stateinfo_get_target_system(msg);
    planck_stateinfo->target_component = mavlink_msg_planck_stateinfo_get_target_component(msg);
    planck_stateinfo->mode = mavlink_msg_planck_stateinfo_get_mode(msg);
    planck_stateinfo->status = mavlink_msg_planck_stateinfo_get_status(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_PLANCK_STATEINFO_LEN? msg->len : MAVLINK_MSG_ID_PLANCK_STATEINFO_LEN;
        memset(planck_stateinfo, 0, MAVLINK_MSG_ID_PLANCK_STATEINFO_LEN);
    memcpy(planck_stateinfo, _MAV_PAYLOAD(msg), len);
#endif
}
