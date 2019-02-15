#pragma once
// MESSAGE LEAD_FOLLOW_COMMAND PACKING

#define MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND 9238

MAVPACKED(
typedef struct __mavlink_lead_follow_command_t {
 float altitude; /*<  Altitude in meters at which lead/follow takes place*/
 float x_offset; /*<  Maintain x distance from landing platform (forward-positive for platform-frame, north-positive for earth-frame)*/
 float y_offset; /*<  Maintain y distance from landing platform (starboard-positive for platform-frame, east-positive for earth-frame)*/
 uint32_t target; /*<  Target to track (LANDING-PLATFORM=0, >0 indicates target ID to track)*/
 uint8_t target_system; /*<  System ID*/
 uint8_t target_component; /*<  Component ID*/
 uint8_t frame; /*<  Reference frame (NORTH-EAST-DOWN=0, FORWARD-STARBOARD-DOWN=1)*/
}) mavlink_lead_follow_command_t;

#define MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND_LEN 19
#define MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND_MIN_LEN 19
#define MAVLINK_MSG_ID_9238_LEN 19
#define MAVLINK_MSG_ID_9238_MIN_LEN 19

#define MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND_CRC 175
#define MAVLINK_MSG_ID_9238_CRC 175



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_LEAD_FOLLOW_COMMAND { \
    9238, \
    "LEAD_FOLLOW_COMMAND", \
    7, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 16, offsetof(mavlink_lead_follow_command_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 17, offsetof(mavlink_lead_follow_command_t, target_component) }, \
         { "altitude", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_lead_follow_command_t, altitude) }, \
         { "x_offset", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_lead_follow_command_t, x_offset) }, \
         { "y_offset", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_lead_follow_command_t, y_offset) }, \
         { "frame", NULL, MAVLINK_TYPE_UINT8_T, 0, 18, offsetof(mavlink_lead_follow_command_t, frame) }, \
         { "target", NULL, MAVLINK_TYPE_UINT32_T, 0, 12, offsetof(mavlink_lead_follow_command_t, target) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_LEAD_FOLLOW_COMMAND { \
    "LEAD_FOLLOW_COMMAND", \
    7, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 16, offsetof(mavlink_lead_follow_command_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 17, offsetof(mavlink_lead_follow_command_t, target_component) }, \
         { "altitude", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_lead_follow_command_t, altitude) }, \
         { "x_offset", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_lead_follow_command_t, x_offset) }, \
         { "y_offset", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_lead_follow_command_t, y_offset) }, \
         { "frame", NULL, MAVLINK_TYPE_UINT8_T, 0, 18, offsetof(mavlink_lead_follow_command_t, frame) }, \
         { "target", NULL, MAVLINK_TYPE_UINT32_T, 0, 12, offsetof(mavlink_lead_follow_command_t, target) }, \
         } \
}
#endif

/**
 * @brief Pack a lead_follow_command message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system  System ID
 * @param target_component  Component ID
 * @param altitude  Altitude in meters at which lead/follow takes place
 * @param x_offset  Maintain x distance from landing platform (forward-positive for platform-frame, north-positive for earth-frame)
 * @param y_offset  Maintain y distance from landing platform (starboard-positive for platform-frame, east-positive for earth-frame)
 * @param frame  Reference frame (NORTH-EAST-DOWN=0, FORWARD-STARBOARD-DOWN=1)
 * @param target  Target to track (LANDING-PLATFORM=0, >0 indicates target ID to track)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_lead_follow_command_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t target_system, uint8_t target_component, float altitude, float x_offset, float y_offset, uint8_t frame, uint32_t target)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND_LEN];
    _mav_put_float(buf, 0, altitude);
    _mav_put_float(buf, 4, x_offset);
    _mav_put_float(buf, 8, y_offset);
    _mav_put_uint32_t(buf, 12, target);
    _mav_put_uint8_t(buf, 16, target_system);
    _mav_put_uint8_t(buf, 17, target_component);
    _mav_put_uint8_t(buf, 18, frame);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND_LEN);
#else
    mavlink_lead_follow_command_t packet;
    packet.altitude = altitude;
    packet.x_offset = x_offset;
    packet.y_offset = y_offset;
    packet.target = target;
    packet.target_system = target_system;
    packet.target_component = target_component;
    packet.frame = frame;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND_MIN_LEN, MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND_LEN, MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND_CRC);
}

/**
 * @brief Pack a lead_follow_command message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system  System ID
 * @param target_component  Component ID
 * @param altitude  Altitude in meters at which lead/follow takes place
 * @param x_offset  Maintain x distance from landing platform (forward-positive for platform-frame, north-positive for earth-frame)
 * @param y_offset  Maintain y distance from landing platform (starboard-positive for platform-frame, east-positive for earth-frame)
 * @param frame  Reference frame (NORTH-EAST-DOWN=0, FORWARD-STARBOARD-DOWN=1)
 * @param target  Target to track (LANDING-PLATFORM=0, >0 indicates target ID to track)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_lead_follow_command_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t target_system,uint8_t target_component,float altitude,float x_offset,float y_offset,uint8_t frame,uint32_t target)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND_LEN];
    _mav_put_float(buf, 0, altitude);
    _mav_put_float(buf, 4, x_offset);
    _mav_put_float(buf, 8, y_offset);
    _mav_put_uint32_t(buf, 12, target);
    _mav_put_uint8_t(buf, 16, target_system);
    _mav_put_uint8_t(buf, 17, target_component);
    _mav_put_uint8_t(buf, 18, frame);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND_LEN);
#else
    mavlink_lead_follow_command_t packet;
    packet.altitude = altitude;
    packet.x_offset = x_offset;
    packet.y_offset = y_offset;
    packet.target = target;
    packet.target_system = target_system;
    packet.target_component = target_component;
    packet.frame = frame;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND_MIN_LEN, MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND_LEN, MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND_CRC);
}

/**
 * @brief Encode a lead_follow_command struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param lead_follow_command C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_lead_follow_command_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_lead_follow_command_t* lead_follow_command)
{
    return mavlink_msg_lead_follow_command_pack(system_id, component_id, msg, lead_follow_command->target_system, lead_follow_command->target_component, lead_follow_command->altitude, lead_follow_command->x_offset, lead_follow_command->y_offset, lead_follow_command->frame, lead_follow_command->target);
}

/**
 * @brief Encode a lead_follow_command struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param lead_follow_command C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_lead_follow_command_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_lead_follow_command_t* lead_follow_command)
{
    return mavlink_msg_lead_follow_command_pack_chan(system_id, component_id, chan, msg, lead_follow_command->target_system, lead_follow_command->target_component, lead_follow_command->altitude, lead_follow_command->x_offset, lead_follow_command->y_offset, lead_follow_command->frame, lead_follow_command->target);
}

/**
 * @brief Send a lead_follow_command message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system  System ID
 * @param target_component  Component ID
 * @param altitude  Altitude in meters at which lead/follow takes place
 * @param x_offset  Maintain x distance from landing platform (forward-positive for platform-frame, north-positive for earth-frame)
 * @param y_offset  Maintain y distance from landing platform (starboard-positive for platform-frame, east-positive for earth-frame)
 * @param frame  Reference frame (NORTH-EAST-DOWN=0, FORWARD-STARBOARD-DOWN=1)
 * @param target  Target to track (LANDING-PLATFORM=0, >0 indicates target ID to track)
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_lead_follow_command_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, float altitude, float x_offset, float y_offset, uint8_t frame, uint32_t target)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND_LEN];
    _mav_put_float(buf, 0, altitude);
    _mav_put_float(buf, 4, x_offset);
    _mav_put_float(buf, 8, y_offset);
    _mav_put_uint32_t(buf, 12, target);
    _mav_put_uint8_t(buf, 16, target_system);
    _mav_put_uint8_t(buf, 17, target_component);
    _mav_put_uint8_t(buf, 18, frame);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND, buf, MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND_MIN_LEN, MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND_LEN, MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND_CRC);
#else
    mavlink_lead_follow_command_t packet;
    packet.altitude = altitude;
    packet.x_offset = x_offset;
    packet.y_offset = y_offset;
    packet.target = target;
    packet.target_system = target_system;
    packet.target_component = target_component;
    packet.frame = frame;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND, (const char *)&packet, MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND_MIN_LEN, MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND_LEN, MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND_CRC);
#endif
}

/**
 * @brief Send a lead_follow_command message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_lead_follow_command_send_struct(mavlink_channel_t chan, const mavlink_lead_follow_command_t* lead_follow_command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_lead_follow_command_send(chan, lead_follow_command->target_system, lead_follow_command->target_component, lead_follow_command->altitude, lead_follow_command->x_offset, lead_follow_command->y_offset, lead_follow_command->frame, lead_follow_command->target);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND, (const char *)lead_follow_command, MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND_MIN_LEN, MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND_LEN, MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND_CRC);
#endif
}

#if MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_lead_follow_command_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t target_system, uint8_t target_component, float altitude, float x_offset, float y_offset, uint8_t frame, uint32_t target)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, altitude);
    _mav_put_float(buf, 4, x_offset);
    _mav_put_float(buf, 8, y_offset);
    _mav_put_uint32_t(buf, 12, target);
    _mav_put_uint8_t(buf, 16, target_system);
    _mav_put_uint8_t(buf, 17, target_component);
    _mav_put_uint8_t(buf, 18, frame);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND, buf, MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND_MIN_LEN, MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND_LEN, MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND_CRC);
#else
    mavlink_lead_follow_command_t *packet = (mavlink_lead_follow_command_t *)msgbuf;
    packet->altitude = altitude;
    packet->x_offset = x_offset;
    packet->y_offset = y_offset;
    packet->target = target;
    packet->target_system = target_system;
    packet->target_component = target_component;
    packet->frame = frame;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND, (const char *)packet, MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND_MIN_LEN, MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND_LEN, MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND_CRC);
#endif
}
#endif

#endif

// MESSAGE LEAD_FOLLOW_COMMAND UNPACKING


/**
 * @brief Get field target_system from lead_follow_command message
 *
 * @return  System ID
 */
static inline uint8_t mavlink_msg_lead_follow_command_get_target_system(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  16);
}

/**
 * @brief Get field target_component from lead_follow_command message
 *
 * @return  Component ID
 */
static inline uint8_t mavlink_msg_lead_follow_command_get_target_component(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  17);
}

/**
 * @brief Get field altitude from lead_follow_command message
 *
 * @return  Altitude in meters at which lead/follow takes place
 */
static inline float mavlink_msg_lead_follow_command_get_altitude(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field x_offset from lead_follow_command message
 *
 * @return  Maintain x distance from landing platform (forward-positive for platform-frame, north-positive for earth-frame)
 */
static inline float mavlink_msg_lead_follow_command_get_x_offset(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field y_offset from lead_follow_command message
 *
 * @return  Maintain y distance from landing platform (starboard-positive for platform-frame, east-positive for earth-frame)
 */
static inline float mavlink_msg_lead_follow_command_get_y_offset(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field frame from lead_follow_command message
 *
 * @return  Reference frame (NORTH-EAST-DOWN=0, FORWARD-STARBOARD-DOWN=1)
 */
static inline uint8_t mavlink_msg_lead_follow_command_get_frame(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  18);
}

/**
 * @brief Get field target from lead_follow_command message
 *
 * @return  Target to track (LANDING-PLATFORM=0, >0 indicates target ID to track)
 */
static inline uint32_t mavlink_msg_lead_follow_command_get_target(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  12);
}

/**
 * @brief Decode a lead_follow_command message into a struct
 *
 * @param msg The message to decode
 * @param lead_follow_command C-struct to decode the message contents into
 */
static inline void mavlink_msg_lead_follow_command_decode(const mavlink_message_t* msg, mavlink_lead_follow_command_t* lead_follow_command)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    lead_follow_command->altitude = mavlink_msg_lead_follow_command_get_altitude(msg);
    lead_follow_command->x_offset = mavlink_msg_lead_follow_command_get_x_offset(msg);
    lead_follow_command->y_offset = mavlink_msg_lead_follow_command_get_y_offset(msg);
    lead_follow_command->target = mavlink_msg_lead_follow_command_get_target(msg);
    lead_follow_command->target_system = mavlink_msg_lead_follow_command_get_target_system(msg);
    lead_follow_command->target_component = mavlink_msg_lead_follow_command_get_target_component(msg);
    lead_follow_command->frame = mavlink_msg_lead_follow_command_get_frame(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND_LEN? msg->len : MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND_LEN;
        memset(lead_follow_command, 0, MAVLINK_MSG_ID_LEAD_FOLLOW_COMMAND_LEN);
    memcpy(lead_follow_command, _MAV_PAYLOAD(msg), len);
#endif
}
