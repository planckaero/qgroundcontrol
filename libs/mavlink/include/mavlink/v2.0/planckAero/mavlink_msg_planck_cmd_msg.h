#pragma once
// MESSAGE PLANCK_CMD_MSG PACKING

#define MAVLINK_MSG_ID_PLANCK_CMD_MSG 9004

MAVPACKED(
typedef struct __mavlink_planck_cmd_msg_t {
 int32_t lat; /*< [degE7] Latitude deg * 1E7*/
 int32_t lon; /*< [degE7] Longitude deg * 1E7*/
 float alt; /*< [m] Altitude in meters*/
 float vel[3]; /*< [m/s] Velocities (NED)*/
 float acc[3]; /*< [m/s/s] Accelerations (NED)*/
 float att[3]; /*< [rads] Attitudes (NED)*/
 uint16_t type_mask; /*<  Fields which are valid: b1:lat, b2:lon, b3:alt, b4:vx, b5:vy, b6:vz, b7:ax, b8:ay, b9:az, b10:roll, b11:pitch, b12:yaw, b13:yaw is rate*/
 uint8_t target_system; /*<  System which should execute the command*/
 uint8_t target_component; /*<  Component which should execute the command, 0 for all components*/
 uint8_t frame; /*<  mav frame, see MAV_FRAME enum*/
}) mavlink_planck_cmd_msg_t;

#define MAVLINK_MSG_ID_PLANCK_CMD_MSG_LEN 53
#define MAVLINK_MSG_ID_PLANCK_CMD_MSG_MIN_LEN 53
#define MAVLINK_MSG_ID_9004_LEN 53
#define MAVLINK_MSG_ID_9004_MIN_LEN 53

#define MAVLINK_MSG_ID_PLANCK_CMD_MSG_CRC 72
#define MAVLINK_MSG_ID_9004_CRC 72

#define MAVLINK_MSG_PLANCK_CMD_MSG_FIELD_VEL_LEN 3
#define MAVLINK_MSG_PLANCK_CMD_MSG_FIELD_ACC_LEN 3
#define MAVLINK_MSG_PLANCK_CMD_MSG_FIELD_ATT_LEN 3

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_PLANCK_CMD_MSG { \
    9004, \
    "PLANCK_CMD_MSG", \
    10, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 50, offsetof(mavlink_planck_cmd_msg_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 51, offsetof(mavlink_planck_cmd_msg_t, target_component) }, \
         { "frame", NULL, MAVLINK_TYPE_UINT8_T, 0, 52, offsetof(mavlink_planck_cmd_msg_t, frame) }, \
         { "type_mask", NULL, MAVLINK_TYPE_UINT16_T, 0, 48, offsetof(mavlink_planck_cmd_msg_t, type_mask) }, \
         { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 0, offsetof(mavlink_planck_cmd_msg_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 4, offsetof(mavlink_planck_cmd_msg_t, lon) }, \
         { "alt", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_planck_cmd_msg_t, alt) }, \
         { "vel", NULL, MAVLINK_TYPE_FLOAT, 3, 12, offsetof(mavlink_planck_cmd_msg_t, vel) }, \
         { "acc", NULL, MAVLINK_TYPE_FLOAT, 3, 24, offsetof(mavlink_planck_cmd_msg_t, acc) }, \
         { "att", NULL, MAVLINK_TYPE_FLOAT, 3, 36, offsetof(mavlink_planck_cmd_msg_t, att) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_PLANCK_CMD_MSG { \
    "PLANCK_CMD_MSG", \
    10, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 50, offsetof(mavlink_planck_cmd_msg_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 51, offsetof(mavlink_planck_cmd_msg_t, target_component) }, \
         { "frame", NULL, MAVLINK_TYPE_UINT8_T, 0, 52, offsetof(mavlink_planck_cmd_msg_t, frame) }, \
         { "type_mask", NULL, MAVLINK_TYPE_UINT16_T, 0, 48, offsetof(mavlink_planck_cmd_msg_t, type_mask) }, \
         { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 0, offsetof(mavlink_planck_cmd_msg_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 4, offsetof(mavlink_planck_cmd_msg_t, lon) }, \
         { "alt", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_planck_cmd_msg_t, alt) }, \
         { "vel", NULL, MAVLINK_TYPE_FLOAT, 3, 12, offsetof(mavlink_planck_cmd_msg_t, vel) }, \
         { "acc", NULL, MAVLINK_TYPE_FLOAT, 3, 24, offsetof(mavlink_planck_cmd_msg_t, acc) }, \
         { "att", NULL, MAVLINK_TYPE_FLOAT, 3, 36, offsetof(mavlink_planck_cmd_msg_t, att) }, \
         } \
}
#endif

/**
 * @brief Pack a planck_cmd_msg message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system  System which should execute the command
 * @param target_component  Component which should execute the command, 0 for all components
 * @param frame  mav frame, see MAV_FRAME enum
 * @param type_mask  Fields which are valid: b1:lat, b2:lon, b3:alt, b4:vx, b5:vy, b6:vz, b7:ax, b8:ay, b9:az, b10:roll, b11:pitch, b12:yaw, b13:yaw is rate
 * @param lat [degE7] Latitude deg * 1E7
 * @param lon [degE7] Longitude deg * 1E7
 * @param alt [m] Altitude in meters
 * @param vel [m/s] Velocities (NED)
 * @param acc [m/s/s] Accelerations (NED)
 * @param att [rads] Attitudes (NED)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_planck_cmd_msg_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t target_system, uint8_t target_component, uint8_t frame, uint16_t type_mask, int32_t lat, int32_t lon, float alt, const float *vel, const float *acc, const float *att)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLANCK_CMD_MSG_LEN];
    _mav_put_int32_t(buf, 0, lat);
    _mav_put_int32_t(buf, 4, lon);
    _mav_put_float(buf, 8, alt);
    _mav_put_uint16_t(buf, 48, type_mask);
    _mav_put_uint8_t(buf, 50, target_system);
    _mav_put_uint8_t(buf, 51, target_component);
    _mav_put_uint8_t(buf, 52, frame);
    _mav_put_float_array(buf, 12, vel, 3);
    _mav_put_float_array(buf, 24, acc, 3);
    _mav_put_float_array(buf, 36, att, 3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PLANCK_CMD_MSG_LEN);
#else
    mavlink_planck_cmd_msg_t packet;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.type_mask = type_mask;
    packet.target_system = target_system;
    packet.target_component = target_component;
    packet.frame = frame;
    mav_array_memcpy(packet.vel, vel, sizeof(float)*3);
    mav_array_memcpy(packet.acc, acc, sizeof(float)*3);
    mav_array_memcpy(packet.att, att, sizeof(float)*3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PLANCK_CMD_MSG_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PLANCK_CMD_MSG;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_PLANCK_CMD_MSG_MIN_LEN, MAVLINK_MSG_ID_PLANCK_CMD_MSG_LEN, MAVLINK_MSG_ID_PLANCK_CMD_MSG_CRC);
}

/**
 * @brief Pack a planck_cmd_msg message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system  System which should execute the command
 * @param target_component  Component which should execute the command, 0 for all components
 * @param frame  mav frame, see MAV_FRAME enum
 * @param type_mask  Fields which are valid: b1:lat, b2:lon, b3:alt, b4:vx, b5:vy, b6:vz, b7:ax, b8:ay, b9:az, b10:roll, b11:pitch, b12:yaw, b13:yaw is rate
 * @param lat [degE7] Latitude deg * 1E7
 * @param lon [degE7] Longitude deg * 1E7
 * @param alt [m] Altitude in meters
 * @param vel [m/s] Velocities (NED)
 * @param acc [m/s/s] Accelerations (NED)
 * @param att [rads] Attitudes (NED)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_planck_cmd_msg_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t target_system,uint8_t target_component,uint8_t frame,uint16_t type_mask,int32_t lat,int32_t lon,float alt,const float *vel,const float *acc,const float *att)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLANCK_CMD_MSG_LEN];
    _mav_put_int32_t(buf, 0, lat);
    _mav_put_int32_t(buf, 4, lon);
    _mav_put_float(buf, 8, alt);
    _mav_put_uint16_t(buf, 48, type_mask);
    _mav_put_uint8_t(buf, 50, target_system);
    _mav_put_uint8_t(buf, 51, target_component);
    _mav_put_uint8_t(buf, 52, frame);
    _mav_put_float_array(buf, 12, vel, 3);
    _mav_put_float_array(buf, 24, acc, 3);
    _mav_put_float_array(buf, 36, att, 3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PLANCK_CMD_MSG_LEN);
#else
    mavlink_planck_cmd_msg_t packet;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.type_mask = type_mask;
    packet.target_system = target_system;
    packet.target_component = target_component;
    packet.frame = frame;
    mav_array_memcpy(packet.vel, vel, sizeof(float)*3);
    mav_array_memcpy(packet.acc, acc, sizeof(float)*3);
    mav_array_memcpy(packet.att, att, sizeof(float)*3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PLANCK_CMD_MSG_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PLANCK_CMD_MSG;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_PLANCK_CMD_MSG_MIN_LEN, MAVLINK_MSG_ID_PLANCK_CMD_MSG_LEN, MAVLINK_MSG_ID_PLANCK_CMD_MSG_CRC);
}

/**
 * @brief Encode a planck_cmd_msg struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param planck_cmd_msg C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_planck_cmd_msg_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_planck_cmd_msg_t* planck_cmd_msg)
{
    return mavlink_msg_planck_cmd_msg_pack(system_id, component_id, msg, planck_cmd_msg->target_system, planck_cmd_msg->target_component, planck_cmd_msg->frame, planck_cmd_msg->type_mask, planck_cmd_msg->lat, planck_cmd_msg->lon, planck_cmd_msg->alt, planck_cmd_msg->vel, planck_cmd_msg->acc, planck_cmd_msg->att);
}

/**
 * @brief Encode a planck_cmd_msg struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param planck_cmd_msg C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_planck_cmd_msg_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_planck_cmd_msg_t* planck_cmd_msg)
{
    return mavlink_msg_planck_cmd_msg_pack_chan(system_id, component_id, chan, msg, planck_cmd_msg->target_system, planck_cmd_msg->target_component, planck_cmd_msg->frame, planck_cmd_msg->type_mask, planck_cmd_msg->lat, planck_cmd_msg->lon, planck_cmd_msg->alt, planck_cmd_msg->vel, planck_cmd_msg->acc, planck_cmd_msg->att);
}

/**
 * @brief Send a planck_cmd_msg message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system  System which should execute the command
 * @param target_component  Component which should execute the command, 0 for all components
 * @param frame  mav frame, see MAV_FRAME enum
 * @param type_mask  Fields which are valid: b1:lat, b2:lon, b3:alt, b4:vx, b5:vy, b6:vz, b7:ax, b8:ay, b9:az, b10:roll, b11:pitch, b12:yaw, b13:yaw is rate
 * @param lat [degE7] Latitude deg * 1E7
 * @param lon [degE7] Longitude deg * 1E7
 * @param alt [m] Altitude in meters
 * @param vel [m/s] Velocities (NED)
 * @param acc [m/s/s] Accelerations (NED)
 * @param att [rads] Attitudes (NED)
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_planck_cmd_msg_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, uint8_t frame, uint16_t type_mask, int32_t lat, int32_t lon, float alt, const float *vel, const float *acc, const float *att)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLANCK_CMD_MSG_LEN];
    _mav_put_int32_t(buf, 0, lat);
    _mav_put_int32_t(buf, 4, lon);
    _mav_put_float(buf, 8, alt);
    _mav_put_uint16_t(buf, 48, type_mask);
    _mav_put_uint8_t(buf, 50, target_system);
    _mav_put_uint8_t(buf, 51, target_component);
    _mav_put_uint8_t(buf, 52, frame);
    _mav_put_float_array(buf, 12, vel, 3);
    _mav_put_float_array(buf, 24, acc, 3);
    _mav_put_float_array(buf, 36, att, 3);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_CMD_MSG, buf, MAVLINK_MSG_ID_PLANCK_CMD_MSG_MIN_LEN, MAVLINK_MSG_ID_PLANCK_CMD_MSG_LEN, MAVLINK_MSG_ID_PLANCK_CMD_MSG_CRC);
#else
    mavlink_planck_cmd_msg_t packet;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.type_mask = type_mask;
    packet.target_system = target_system;
    packet.target_component = target_component;
    packet.frame = frame;
    mav_array_memcpy(packet.vel, vel, sizeof(float)*3);
    mav_array_memcpy(packet.acc, acc, sizeof(float)*3);
    mav_array_memcpy(packet.att, att, sizeof(float)*3);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_CMD_MSG, (const char *)&packet, MAVLINK_MSG_ID_PLANCK_CMD_MSG_MIN_LEN, MAVLINK_MSG_ID_PLANCK_CMD_MSG_LEN, MAVLINK_MSG_ID_PLANCK_CMD_MSG_CRC);
#endif
}

/**
 * @brief Send a planck_cmd_msg message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_planck_cmd_msg_send_struct(mavlink_channel_t chan, const mavlink_planck_cmd_msg_t* planck_cmd_msg)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_planck_cmd_msg_send(chan, planck_cmd_msg->target_system, planck_cmd_msg->target_component, planck_cmd_msg->frame, planck_cmd_msg->type_mask, planck_cmd_msg->lat, planck_cmd_msg->lon, planck_cmd_msg->alt, planck_cmd_msg->vel, planck_cmd_msg->acc, planck_cmd_msg->att);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_CMD_MSG, (const char *)planck_cmd_msg, MAVLINK_MSG_ID_PLANCK_CMD_MSG_MIN_LEN, MAVLINK_MSG_ID_PLANCK_CMD_MSG_LEN, MAVLINK_MSG_ID_PLANCK_CMD_MSG_CRC);
#endif
}

#if MAVLINK_MSG_ID_PLANCK_CMD_MSG_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_planck_cmd_msg_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t target_system, uint8_t target_component, uint8_t frame, uint16_t type_mask, int32_t lat, int32_t lon, float alt, const float *vel, const float *acc, const float *att)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int32_t(buf, 0, lat);
    _mav_put_int32_t(buf, 4, lon);
    _mav_put_float(buf, 8, alt);
    _mav_put_uint16_t(buf, 48, type_mask);
    _mav_put_uint8_t(buf, 50, target_system);
    _mav_put_uint8_t(buf, 51, target_component);
    _mav_put_uint8_t(buf, 52, frame);
    _mav_put_float_array(buf, 12, vel, 3);
    _mav_put_float_array(buf, 24, acc, 3);
    _mav_put_float_array(buf, 36, att, 3);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_CMD_MSG, buf, MAVLINK_MSG_ID_PLANCK_CMD_MSG_MIN_LEN, MAVLINK_MSG_ID_PLANCK_CMD_MSG_LEN, MAVLINK_MSG_ID_PLANCK_CMD_MSG_CRC);
#else
    mavlink_planck_cmd_msg_t *packet = (mavlink_planck_cmd_msg_t *)msgbuf;
    packet->lat = lat;
    packet->lon = lon;
    packet->alt = alt;
    packet->type_mask = type_mask;
    packet->target_system = target_system;
    packet->target_component = target_component;
    packet->frame = frame;
    mav_array_memcpy(packet->vel, vel, sizeof(float)*3);
    mav_array_memcpy(packet->acc, acc, sizeof(float)*3);
    mav_array_memcpy(packet->att, att, sizeof(float)*3);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_CMD_MSG, (const char *)packet, MAVLINK_MSG_ID_PLANCK_CMD_MSG_MIN_LEN, MAVLINK_MSG_ID_PLANCK_CMD_MSG_LEN, MAVLINK_MSG_ID_PLANCK_CMD_MSG_CRC);
#endif
}
#endif

#endif

// MESSAGE PLANCK_CMD_MSG UNPACKING


/**
 * @brief Get field target_system from planck_cmd_msg message
 *
 * @return  System which should execute the command
 */
static inline uint8_t mavlink_msg_planck_cmd_msg_get_target_system(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  50);
}

/**
 * @brief Get field target_component from planck_cmd_msg message
 *
 * @return  Component which should execute the command, 0 for all components
 */
static inline uint8_t mavlink_msg_planck_cmd_msg_get_target_component(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  51);
}

/**
 * @brief Get field frame from planck_cmd_msg message
 *
 * @return  mav frame, see MAV_FRAME enum
 */
static inline uint8_t mavlink_msg_planck_cmd_msg_get_frame(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  52);
}

/**
 * @brief Get field type_mask from planck_cmd_msg message
 *
 * @return  Fields which are valid: b1:lat, b2:lon, b3:alt, b4:vx, b5:vy, b6:vz, b7:ax, b8:ay, b9:az, b10:roll, b11:pitch, b12:yaw, b13:yaw is rate
 */
static inline uint16_t mavlink_msg_planck_cmd_msg_get_type_mask(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  48);
}

/**
 * @brief Get field lat from planck_cmd_msg message
 *
 * @return [degE7] Latitude deg * 1E7
 */
static inline int32_t mavlink_msg_planck_cmd_msg_get_lat(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  0);
}

/**
 * @brief Get field lon from planck_cmd_msg message
 *
 * @return [degE7] Longitude deg * 1E7
 */
static inline int32_t mavlink_msg_planck_cmd_msg_get_lon(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  4);
}

/**
 * @brief Get field alt from planck_cmd_msg message
 *
 * @return [m] Altitude in meters
 */
static inline float mavlink_msg_planck_cmd_msg_get_alt(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field vel from planck_cmd_msg message
 *
 * @return [m/s] Velocities (NED)
 */
static inline uint16_t mavlink_msg_planck_cmd_msg_get_vel(const mavlink_message_t* msg, float *vel)
{
    return _MAV_RETURN_float_array(msg, vel, 3,  12);
}

/**
 * @brief Get field acc from planck_cmd_msg message
 *
 * @return [m/s/s] Accelerations (NED)
 */
static inline uint16_t mavlink_msg_planck_cmd_msg_get_acc(const mavlink_message_t* msg, float *acc)
{
    return _MAV_RETURN_float_array(msg, acc, 3,  24);
}

/**
 * @brief Get field att from planck_cmd_msg message
 *
 * @return [rads] Attitudes (NED)
 */
static inline uint16_t mavlink_msg_planck_cmd_msg_get_att(const mavlink_message_t* msg, float *att)
{
    return _MAV_RETURN_float_array(msg, att, 3,  36);
}

/**
 * @brief Decode a planck_cmd_msg message into a struct
 *
 * @param msg The message to decode
 * @param planck_cmd_msg C-struct to decode the message contents into
 */
static inline void mavlink_msg_planck_cmd_msg_decode(const mavlink_message_t* msg, mavlink_planck_cmd_msg_t* planck_cmd_msg)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    planck_cmd_msg->lat = mavlink_msg_planck_cmd_msg_get_lat(msg);
    planck_cmd_msg->lon = mavlink_msg_planck_cmd_msg_get_lon(msg);
    planck_cmd_msg->alt = mavlink_msg_planck_cmd_msg_get_alt(msg);
    mavlink_msg_planck_cmd_msg_get_vel(msg, planck_cmd_msg->vel);
    mavlink_msg_planck_cmd_msg_get_acc(msg, planck_cmd_msg->acc);
    mavlink_msg_planck_cmd_msg_get_att(msg, planck_cmd_msg->att);
    planck_cmd_msg->type_mask = mavlink_msg_planck_cmd_msg_get_type_mask(msg);
    planck_cmd_msg->target_system = mavlink_msg_planck_cmd_msg_get_target_system(msg);
    planck_cmd_msg->target_component = mavlink_msg_planck_cmd_msg_get_target_component(msg);
    planck_cmd_msg->frame = mavlink_msg_planck_cmd_msg_get_frame(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_PLANCK_CMD_MSG_LEN? msg->len : MAVLINK_MSG_ID_PLANCK_CMD_MSG_LEN;
        memset(planck_cmd_msg, 0, MAVLINK_MSG_ID_PLANCK_CMD_MSG_LEN);
    memcpy(planck_cmd_msg, _MAV_PAYLOAD(msg), len);
#endif
}
