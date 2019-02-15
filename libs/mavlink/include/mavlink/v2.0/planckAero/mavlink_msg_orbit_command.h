#pragma once
// MESSAGE ORBIT_COMMAND PACKING

#define MAVLINK_MSG_ID_ORBIT_COMMAND 237

MAVPACKED(
typedef struct __mavlink_orbit_command_t {
 float altitude; /*< Altitude in meters at which orbit takes place*/
 float angular_velocity; /*< Rate in rad/sec at which to orbit (positive=clockwise)*/
 float radius; /*< Distance in meters from center of landing platform to orbit*/
 float orientation; /*< vehicle direction during orbit (away-relative, positive-right, example: 0=outward)*/
 uint32_t target; /*< Target to track (LANDING-PLATFORM=0, >0 indicates target ID to track)*/
 uint8_t target_system; /*< System ID*/
 uint8_t target_component; /*< Component ID*/
}) mavlink_orbit_command_t;

#define MAVLINK_MSG_ID_ORBIT_COMMAND_LEN 22
#define MAVLINK_MSG_ID_ORBIT_COMMAND_MIN_LEN 22
#define MAVLINK_MSG_ID_237_LEN 22
#define MAVLINK_MSG_ID_237_MIN_LEN 22

#define MAVLINK_MSG_ID_ORBIT_COMMAND_CRC 133
#define MAVLINK_MSG_ID_237_CRC 133



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_ORBIT_COMMAND { \
    237, \
    "ORBIT_COMMAND", \
    7, \
    {  { "altitude", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_orbit_command_t, altitude) }, \
         { "angular_velocity", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_orbit_command_t, angular_velocity) }, \
         { "radius", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_orbit_command_t, radius) }, \
         { "orientation", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_orbit_command_t, orientation) }, \
         { "target", NULL, MAVLINK_TYPE_UINT32_T, 0, 16, offsetof(mavlink_orbit_command_t, target) }, \
         { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 20, offsetof(mavlink_orbit_command_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 21, offsetof(mavlink_orbit_command_t, target_component) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_ORBIT_COMMAND { \
    "ORBIT_COMMAND", \
    7, \
    {  { "altitude", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_orbit_command_t, altitude) }, \
         { "angular_velocity", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_orbit_command_t, angular_velocity) }, \
         { "radius", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_orbit_command_t, radius) }, \
         { "orientation", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_orbit_command_t, orientation) }, \
         { "target", NULL, MAVLINK_TYPE_UINT32_T, 0, 16, offsetof(mavlink_orbit_command_t, target) }, \
         { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 20, offsetof(mavlink_orbit_command_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 21, offsetof(mavlink_orbit_command_t, target_component) }, \
         } \
}
#endif

/**
 * @brief Pack a orbit_command message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param altitude Altitude in meters at which orbit takes place
 * @param angular_velocity Rate in rad/sec at which to orbit (positive=clockwise)
 * @param radius Distance in meters from center of landing platform to orbit
 * @param orientation vehicle direction during orbit (away-relative, positive-right, example: 0=outward)
 * @param target Target to track (LANDING-PLATFORM=0, >0 indicates target ID to track)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_orbit_command_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t target_system, uint8_t target_component, float altitude, float angular_velocity, float radius, float orientation, uint32_t target)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ORBIT_COMMAND_LEN];
    _mav_put_float(buf, 0, altitude);
    _mav_put_float(buf, 4, angular_velocity);
    _mav_put_float(buf, 8, radius);
    _mav_put_float(buf, 12, orientation);
    _mav_put_uint32_t(buf, 16, target);
    _mav_put_uint8_t(buf, 20, target_system);
    _mav_put_uint8_t(buf, 21, target_component);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ORBIT_COMMAND_LEN);
#else
    mavlink_orbit_command_t packet;
    packet.altitude = altitude;
    packet.angular_velocity = angular_velocity;
    packet.radius = radius;
    packet.orientation = orientation;
    packet.target = target;
    packet.target_system = target_system;
    packet.target_component = target_component;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ORBIT_COMMAND_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ORBIT_COMMAND;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ORBIT_COMMAND_MIN_LEN, MAVLINK_MSG_ID_ORBIT_COMMAND_LEN, MAVLINK_MSG_ID_ORBIT_COMMAND_CRC);
}

/**
 * @brief Pack a orbit_command message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system System ID
 * @param target_component Component ID
 * @param altitude Altitude in meters at which orbit takes place
 * @param angular_velocity Rate in rad/sec at which to orbit (positive=clockwise)
 * @param radius Distance in meters from center of landing platform to orbit
 * @param orientation vehicle direction during orbit (away-relative, positive-right, example: 0=outward)
 * @param target Target to track (LANDING-PLATFORM=0, >0 indicates target ID to track)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_orbit_command_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t target_system,uint8_t target_component,float altitude,float angular_velocity,float radius,float orientation,uint32_t target)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ORBIT_COMMAND_LEN];
    _mav_put_float(buf, 0, altitude);
    _mav_put_float(buf, 4, angular_velocity);
    _mav_put_float(buf, 8, radius);
    _mav_put_float(buf, 12, orientation);
    _mav_put_uint32_t(buf, 16, target);
    _mav_put_uint8_t(buf, 20, target_system);
    _mav_put_uint8_t(buf, 21, target_component);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ORBIT_COMMAND_LEN);
#else
    mavlink_orbit_command_t packet;
    packet.altitude = altitude;
    packet.angular_velocity = angular_velocity;
    packet.radius = radius;
    packet.orientation = orientation;
    packet.target = target;
    packet.target_system = target_system;
    packet.target_component = target_component;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ORBIT_COMMAND_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ORBIT_COMMAND;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ORBIT_COMMAND_MIN_LEN, MAVLINK_MSG_ID_ORBIT_COMMAND_LEN, MAVLINK_MSG_ID_ORBIT_COMMAND_CRC);
}

/**
 * @brief Encode a orbit_command struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param orbit_command C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_orbit_command_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_orbit_command_t* orbit_command)
{
    return mavlink_msg_orbit_command_pack(system_id, component_id, msg, orbit_command->target_system, orbit_command->target_component, orbit_command->altitude, orbit_command->angular_velocity, orbit_command->radius, orbit_command->orientation, orbit_command->target);
}

/**
 * @brief Encode a orbit_command struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param orbit_command C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_orbit_command_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_orbit_command_t* orbit_command)
{
    return mavlink_msg_orbit_command_pack_chan(system_id, component_id, chan, msg, orbit_command->target_system, orbit_command->target_component, orbit_command->altitude, orbit_command->angular_velocity, orbit_command->radius, orbit_command->orientation, orbit_command->target);
}

/**
 * @brief Send a orbit_command message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param altitude Altitude in meters at which orbit takes place
 * @param angular_velocity Rate in rad/sec at which to orbit (positive=clockwise)
 * @param radius Distance in meters from center of landing platform to orbit
 * @param orientation vehicle direction during orbit (away-relative, positive-right, example: 0=outward)
 * @param target Target to track (LANDING-PLATFORM=0, >0 indicates target ID to track)
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_orbit_command_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, float altitude, float angular_velocity, float radius, float orientation, uint32_t target)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ORBIT_COMMAND_LEN];
    _mav_put_float(buf, 0, altitude);
    _mav_put_float(buf, 4, angular_velocity);
    _mav_put_float(buf, 8, radius);
    _mav_put_float(buf, 12, orientation);
    _mav_put_uint32_t(buf, 16, target);
    _mav_put_uint8_t(buf, 20, target_system);
    _mav_put_uint8_t(buf, 21, target_component);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ORBIT_COMMAND, buf, MAVLINK_MSG_ID_ORBIT_COMMAND_MIN_LEN, MAVLINK_MSG_ID_ORBIT_COMMAND_LEN, MAVLINK_MSG_ID_ORBIT_COMMAND_CRC);
#else
    mavlink_orbit_command_t packet;
    packet.altitude = altitude;
    packet.angular_velocity = angular_velocity;
    packet.radius = radius;
    packet.orientation = orientation;
    packet.target = target;
    packet.target_system = target_system;
    packet.target_component = target_component;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ORBIT_COMMAND, (const char *)&packet, MAVLINK_MSG_ID_ORBIT_COMMAND_MIN_LEN, MAVLINK_MSG_ID_ORBIT_COMMAND_LEN, MAVLINK_MSG_ID_ORBIT_COMMAND_CRC);
#endif
}

/**
 * @brief Send a orbit_command message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_orbit_command_send_struct(mavlink_channel_t chan, const mavlink_orbit_command_t* orbit_command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_orbit_command_send(chan, orbit_command->target_system, orbit_command->target_component, orbit_command->altitude, orbit_command->angular_velocity, orbit_command->radius, orbit_command->orientation, orbit_command->target);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ORBIT_COMMAND, (const char *)orbit_command, MAVLINK_MSG_ID_ORBIT_COMMAND_MIN_LEN, MAVLINK_MSG_ID_ORBIT_COMMAND_LEN, MAVLINK_MSG_ID_ORBIT_COMMAND_CRC);
#endif
}

#if MAVLINK_MSG_ID_ORBIT_COMMAND_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_orbit_command_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t target_system, uint8_t target_component, float altitude, float angular_velocity, float radius, float orientation, uint32_t target)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, altitude);
    _mav_put_float(buf, 4, angular_velocity);
    _mav_put_float(buf, 8, radius);
    _mav_put_float(buf, 12, orientation);
    _mav_put_uint32_t(buf, 16, target);
    _mav_put_uint8_t(buf, 20, target_system);
    _mav_put_uint8_t(buf, 21, target_component);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ORBIT_COMMAND, buf, MAVLINK_MSG_ID_ORBIT_COMMAND_MIN_LEN, MAVLINK_MSG_ID_ORBIT_COMMAND_LEN, MAVLINK_MSG_ID_ORBIT_COMMAND_CRC);
#else
    mavlink_orbit_command_t *packet = (mavlink_orbit_command_t *)msgbuf;
    packet->altitude = altitude;
    packet->angular_velocity = angular_velocity;
    packet->radius = radius;
    packet->orientation = orientation;
    packet->target = target;
    packet->target_system = target_system;
    packet->target_component = target_component;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ORBIT_COMMAND, (const char *)packet, MAVLINK_MSG_ID_ORBIT_COMMAND_MIN_LEN, MAVLINK_MSG_ID_ORBIT_COMMAND_LEN, MAVLINK_MSG_ID_ORBIT_COMMAND_CRC);
#endif
}
#endif

#endif

// MESSAGE ORBIT_COMMAND UNPACKING


/**
 * @brief Get field target_system from orbit_command message
 *
 * @return System ID
 */
static inline uint8_t mavlink_msg_orbit_command_get_target_system(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  20);
}

/**
 * @brief Get field target_component from orbit_command message
 *
 * @return Component ID
 */
static inline uint8_t mavlink_msg_orbit_command_get_target_component(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  21);
}

/**
 * @brief Get field altitude from orbit_command message
 *
 * @return Altitude in meters at which orbit takes place
 */
static inline float mavlink_msg_orbit_command_get_altitude(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field angular_velocity from orbit_command message
 *
 * @return Rate in rad/sec at which to orbit (positive=clockwise)
 */
static inline float mavlink_msg_orbit_command_get_angular_velocity(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field radius from orbit_command message
 *
 * @return Distance in meters from center of landing platform to orbit
 */
static inline float mavlink_msg_orbit_command_get_radius(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field orientation from orbit_command message
 *
 * @return vehicle direction during orbit (away-relative, positive-right, example: 0=outward)
 */
static inline float mavlink_msg_orbit_command_get_orientation(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field target from orbit_command message
 *
 * @return Target to track (LANDING-PLATFORM=0, >0 indicates target ID to track)
 */
static inline uint32_t mavlink_msg_orbit_command_get_target(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  16);
}

/**
 * @brief Decode a orbit_command message into a struct
 *
 * @param msg The message to decode
 * @param orbit_command C-struct to decode the message contents into
 */
static inline void mavlink_msg_orbit_command_decode(const mavlink_message_t* msg, mavlink_orbit_command_t* orbit_command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    orbit_command->altitude = mavlink_msg_orbit_command_get_altitude(msg);
    orbit_command->angular_velocity = mavlink_msg_orbit_command_get_angular_velocity(msg);
    orbit_command->radius = mavlink_msg_orbit_command_get_radius(msg);
    orbit_command->orientation = mavlink_msg_orbit_command_get_orientation(msg);
    orbit_command->target = mavlink_msg_orbit_command_get_target(msg);
    orbit_command->target_system = mavlink_msg_orbit_command_get_target_system(msg);
    orbit_command->target_component = mavlink_msg_orbit_command_get_target_component(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_ORBIT_COMMAND_LEN? msg->len : MAVLINK_MSG_ID_ORBIT_COMMAND_LEN;
        memset(orbit_command, 0, MAVLINK_MSG_ID_ORBIT_COMMAND_LEN);
    memcpy(orbit_command, _MAV_PAYLOAD(msg), len);
#endif
}
