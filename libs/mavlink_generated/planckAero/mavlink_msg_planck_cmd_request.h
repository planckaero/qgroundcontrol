#pragma once
// MESSAGE PLANCK_CMD_REQUEST PACKING

#define MAVLINK_MSG_ID_PLANCK_CMD_REQUEST 9005

MAVPACKED(
typedef struct __mavlink_planck_cmd_request_t {
 float param1; /*<  First parameter (command-specific)*/
 float param2; /*<  Second parameter (command-specific)*/
 float param3; /*<  Third parameter (command-specific)*/
 float param4; /*<  Fourth parameter (command-specific)*/
 float param5; /*<  Fifth parameter (command-specific)*/
 float param6; /*<  Sixth parameter (command-specific)*/
 uint8_t target_system; /*<  System which should execute the command*/
 uint8_t target_component; /*<  Component which should execute the command, 0 for all components*/
 uint8_t type; /*<  Command type (see PLANCK_CMD_REQ_TYPE enum)*/
}) mavlink_planck_cmd_request_t;

#define MAVLINK_MSG_ID_PLANCK_CMD_REQUEST_LEN 27
#define MAVLINK_MSG_ID_PLANCK_CMD_REQUEST_MIN_LEN 27
#define MAVLINK_MSG_ID_9005_LEN 27
#define MAVLINK_MSG_ID_9005_MIN_LEN 27

#define MAVLINK_MSG_ID_PLANCK_CMD_REQUEST_CRC 211
#define MAVLINK_MSG_ID_9005_CRC 211



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_PLANCK_CMD_REQUEST { \
    9005, \
    "PLANCK_CMD_REQUEST", \
    9, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 24, offsetof(mavlink_planck_cmd_request_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 25, offsetof(mavlink_planck_cmd_request_t, target_component) }, \
         { "type", NULL, MAVLINK_TYPE_UINT8_T, 0, 26, offsetof(mavlink_planck_cmd_request_t, type) }, \
         { "param1", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_planck_cmd_request_t, param1) }, \
         { "param2", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_planck_cmd_request_t, param2) }, \
         { "param3", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_planck_cmd_request_t, param3) }, \
         { "param4", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_planck_cmd_request_t, param4) }, \
         { "param5", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_planck_cmd_request_t, param5) }, \
         { "param6", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_planck_cmd_request_t, param6) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_PLANCK_CMD_REQUEST { \
    "PLANCK_CMD_REQUEST", \
    9, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 24, offsetof(mavlink_planck_cmd_request_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 25, offsetof(mavlink_planck_cmd_request_t, target_component) }, \
         { "type", NULL, MAVLINK_TYPE_UINT8_T, 0, 26, offsetof(mavlink_planck_cmd_request_t, type) }, \
         { "param1", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_planck_cmd_request_t, param1) }, \
         { "param2", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_planck_cmd_request_t, param2) }, \
         { "param3", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_planck_cmd_request_t, param3) }, \
         { "param4", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_planck_cmd_request_t, param4) }, \
         { "param5", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_planck_cmd_request_t, param5) }, \
         { "param6", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_planck_cmd_request_t, param6) }, \
         } \
}
#endif

/**
 * @brief Pack a planck_cmd_request message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system  System which should execute the command
 * @param target_component  Component which should execute the command, 0 for all components
 * @param type  Command type (see PLANCK_CMD_REQ_TYPE enum)
 * @param param1  First parameter (command-specific)
 * @param param2  Second parameter (command-specific)
 * @param param3  Third parameter (command-specific)
 * @param param4  Fourth parameter (command-specific)
 * @param param5  Fifth parameter (command-specific)
 * @param param6  Sixth parameter (command-specific)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_planck_cmd_request_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t target_system, uint8_t target_component, uint8_t type, float param1, float param2, float param3, float param4, float param5, float param6)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLANCK_CMD_REQUEST_LEN];
    _mav_put_float(buf, 0, param1);
    _mav_put_float(buf, 4, param2);
    _mav_put_float(buf, 8, param3);
    _mav_put_float(buf, 12, param4);
    _mav_put_float(buf, 16, param5);
    _mav_put_float(buf, 20, param6);
    _mav_put_uint8_t(buf, 24, target_system);
    _mav_put_uint8_t(buf, 25, target_component);
    _mav_put_uint8_t(buf, 26, type);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PLANCK_CMD_REQUEST_LEN);
#else
    mavlink_planck_cmd_request_t packet;
    packet.param1 = param1;
    packet.param2 = param2;
    packet.param3 = param3;
    packet.param4 = param4;
    packet.param5 = param5;
    packet.param6 = param6;
    packet.target_system = target_system;
    packet.target_component = target_component;
    packet.type = type;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PLANCK_CMD_REQUEST_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PLANCK_CMD_REQUEST;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_PLANCK_CMD_REQUEST_MIN_LEN, MAVLINK_MSG_ID_PLANCK_CMD_REQUEST_LEN, MAVLINK_MSG_ID_PLANCK_CMD_REQUEST_CRC);
}

/**
 * @brief Pack a planck_cmd_request message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system  System which should execute the command
 * @param target_component  Component which should execute the command, 0 for all components
 * @param type  Command type (see PLANCK_CMD_REQ_TYPE enum)
 * @param param1  First parameter (command-specific)
 * @param param2  Second parameter (command-specific)
 * @param param3  Third parameter (command-specific)
 * @param param4  Fourth parameter (command-specific)
 * @param param5  Fifth parameter (command-specific)
 * @param param6  Sixth parameter (command-specific)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_planck_cmd_request_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t target_system,uint8_t target_component,uint8_t type,float param1,float param2,float param3,float param4,float param5,float param6)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLANCK_CMD_REQUEST_LEN];
    _mav_put_float(buf, 0, param1);
    _mav_put_float(buf, 4, param2);
    _mav_put_float(buf, 8, param3);
    _mav_put_float(buf, 12, param4);
    _mav_put_float(buf, 16, param5);
    _mav_put_float(buf, 20, param6);
    _mav_put_uint8_t(buf, 24, target_system);
    _mav_put_uint8_t(buf, 25, target_component);
    _mav_put_uint8_t(buf, 26, type);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PLANCK_CMD_REQUEST_LEN);
#else
    mavlink_planck_cmd_request_t packet;
    packet.param1 = param1;
    packet.param2 = param2;
    packet.param3 = param3;
    packet.param4 = param4;
    packet.param5 = param5;
    packet.param6 = param6;
    packet.target_system = target_system;
    packet.target_component = target_component;
    packet.type = type;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PLANCK_CMD_REQUEST_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PLANCK_CMD_REQUEST;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_PLANCK_CMD_REQUEST_MIN_LEN, MAVLINK_MSG_ID_PLANCK_CMD_REQUEST_LEN, MAVLINK_MSG_ID_PLANCK_CMD_REQUEST_CRC);
}

/**
 * @brief Encode a planck_cmd_request struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param planck_cmd_request C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_planck_cmd_request_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_planck_cmd_request_t* planck_cmd_request)
{
    return mavlink_msg_planck_cmd_request_pack(system_id, component_id, msg, planck_cmd_request->target_system, planck_cmd_request->target_component, planck_cmd_request->type, planck_cmd_request->param1, planck_cmd_request->param2, planck_cmd_request->param3, planck_cmd_request->param4, planck_cmd_request->param5, planck_cmd_request->param6);
}

/**
 * @brief Encode a planck_cmd_request struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param planck_cmd_request C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_planck_cmd_request_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_planck_cmd_request_t* planck_cmd_request)
{
    return mavlink_msg_planck_cmd_request_pack_chan(system_id, component_id, chan, msg, planck_cmd_request->target_system, planck_cmd_request->target_component, planck_cmd_request->type, planck_cmd_request->param1, planck_cmd_request->param2, planck_cmd_request->param3, planck_cmd_request->param4, planck_cmd_request->param5, planck_cmd_request->param6);
}

/**
 * @brief Send a planck_cmd_request message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system  System which should execute the command
 * @param target_component  Component which should execute the command, 0 for all components
 * @param type  Command type (see PLANCK_CMD_REQ_TYPE enum)
 * @param param1  First parameter (command-specific)
 * @param param2  Second parameter (command-specific)
 * @param param3  Third parameter (command-specific)
 * @param param4  Fourth parameter (command-specific)
 * @param param5  Fifth parameter (command-specific)
 * @param param6  Sixth parameter (command-specific)
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_planck_cmd_request_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, uint8_t type, float param1, float param2, float param3, float param4, float param5, float param6)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PLANCK_CMD_REQUEST_LEN];
    _mav_put_float(buf, 0, param1);
    _mav_put_float(buf, 4, param2);
    _mav_put_float(buf, 8, param3);
    _mav_put_float(buf, 12, param4);
    _mav_put_float(buf, 16, param5);
    _mav_put_float(buf, 20, param6);
    _mav_put_uint8_t(buf, 24, target_system);
    _mav_put_uint8_t(buf, 25, target_component);
    _mav_put_uint8_t(buf, 26, type);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_CMD_REQUEST, buf, MAVLINK_MSG_ID_PLANCK_CMD_REQUEST_MIN_LEN, MAVLINK_MSG_ID_PLANCK_CMD_REQUEST_LEN, MAVLINK_MSG_ID_PLANCK_CMD_REQUEST_CRC);
#else
    mavlink_planck_cmd_request_t packet;
    packet.param1 = param1;
    packet.param2 = param2;
    packet.param3 = param3;
    packet.param4 = param4;
    packet.param5 = param5;
    packet.param6 = param6;
    packet.target_system = target_system;
    packet.target_component = target_component;
    packet.type = type;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_CMD_REQUEST, (const char *)&packet, MAVLINK_MSG_ID_PLANCK_CMD_REQUEST_MIN_LEN, MAVLINK_MSG_ID_PLANCK_CMD_REQUEST_LEN, MAVLINK_MSG_ID_PLANCK_CMD_REQUEST_CRC);
#endif
}

/**
 * @brief Send a planck_cmd_request message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_planck_cmd_request_send_struct(mavlink_channel_t chan, const mavlink_planck_cmd_request_t* planck_cmd_request)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_planck_cmd_request_send(chan, planck_cmd_request->target_system, planck_cmd_request->target_component, planck_cmd_request->type, planck_cmd_request->param1, planck_cmd_request->param2, planck_cmd_request->param3, planck_cmd_request->param4, planck_cmd_request->param5, planck_cmd_request->param6);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_CMD_REQUEST, (const char *)planck_cmd_request, MAVLINK_MSG_ID_PLANCK_CMD_REQUEST_MIN_LEN, MAVLINK_MSG_ID_PLANCK_CMD_REQUEST_LEN, MAVLINK_MSG_ID_PLANCK_CMD_REQUEST_CRC);
#endif
}

#if MAVLINK_MSG_ID_PLANCK_CMD_REQUEST_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_planck_cmd_request_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t target_system, uint8_t target_component, uint8_t type, float param1, float param2, float param3, float param4, float param5, float param6)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, param1);
    _mav_put_float(buf, 4, param2);
    _mav_put_float(buf, 8, param3);
    _mav_put_float(buf, 12, param4);
    _mav_put_float(buf, 16, param5);
    _mav_put_float(buf, 20, param6);
    _mav_put_uint8_t(buf, 24, target_system);
    _mav_put_uint8_t(buf, 25, target_component);
    _mav_put_uint8_t(buf, 26, type);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_CMD_REQUEST, buf, MAVLINK_MSG_ID_PLANCK_CMD_REQUEST_MIN_LEN, MAVLINK_MSG_ID_PLANCK_CMD_REQUEST_LEN, MAVLINK_MSG_ID_PLANCK_CMD_REQUEST_CRC);
#else
    mavlink_planck_cmd_request_t *packet = (mavlink_planck_cmd_request_t *)msgbuf;
    packet->param1 = param1;
    packet->param2 = param2;
    packet->param3 = param3;
    packet->param4 = param4;
    packet->param5 = param5;
    packet->param6 = param6;
    packet->target_system = target_system;
    packet->target_component = target_component;
    packet->type = type;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PLANCK_CMD_REQUEST, (const char *)packet, MAVLINK_MSG_ID_PLANCK_CMD_REQUEST_MIN_LEN, MAVLINK_MSG_ID_PLANCK_CMD_REQUEST_LEN, MAVLINK_MSG_ID_PLANCK_CMD_REQUEST_CRC);
#endif
}
#endif

#endif

// MESSAGE PLANCK_CMD_REQUEST UNPACKING


/**
 * @brief Get field target_system from planck_cmd_request message
 *
 * @return  System which should execute the command
 */
static inline uint8_t mavlink_msg_planck_cmd_request_get_target_system(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  24);
}

/**
 * @brief Get field target_component from planck_cmd_request message
 *
 * @return  Component which should execute the command, 0 for all components
 */
static inline uint8_t mavlink_msg_planck_cmd_request_get_target_component(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  25);
}

/**
 * @brief Get field type from planck_cmd_request message
 *
 * @return  Command type (see PLANCK_CMD_REQ_TYPE enum)
 */
static inline uint8_t mavlink_msg_planck_cmd_request_get_type(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  26);
}

/**
 * @brief Get field param1 from planck_cmd_request message
 *
 * @return  First parameter (command-specific)
 */
static inline float mavlink_msg_planck_cmd_request_get_param1(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field param2 from planck_cmd_request message
 *
 * @return  Second parameter (command-specific)
 */
static inline float mavlink_msg_planck_cmd_request_get_param2(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field param3 from planck_cmd_request message
 *
 * @return  Third parameter (command-specific)
 */
static inline float mavlink_msg_planck_cmd_request_get_param3(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field param4 from planck_cmd_request message
 *
 * @return  Fourth parameter (command-specific)
 */
static inline float mavlink_msg_planck_cmd_request_get_param4(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field param5 from planck_cmd_request message
 *
 * @return  Fifth parameter (command-specific)
 */
static inline float mavlink_msg_planck_cmd_request_get_param5(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field param6 from planck_cmd_request message
 *
 * @return  Sixth parameter (command-specific)
 */
static inline float mavlink_msg_planck_cmd_request_get_param6(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Decode a planck_cmd_request message into a struct
 *
 * @param msg The message to decode
 * @param planck_cmd_request C-struct to decode the message contents into
 */
static inline void mavlink_msg_planck_cmd_request_decode(const mavlink_message_t* msg, mavlink_planck_cmd_request_t* planck_cmd_request)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    planck_cmd_request->param1 = mavlink_msg_planck_cmd_request_get_param1(msg);
    planck_cmd_request->param2 = mavlink_msg_planck_cmd_request_get_param2(msg);
    planck_cmd_request->param3 = mavlink_msg_planck_cmd_request_get_param3(msg);
    planck_cmd_request->param4 = mavlink_msg_planck_cmd_request_get_param4(msg);
    planck_cmd_request->param5 = mavlink_msg_planck_cmd_request_get_param5(msg);
    planck_cmd_request->param6 = mavlink_msg_planck_cmd_request_get_param6(msg);
    planck_cmd_request->target_system = mavlink_msg_planck_cmd_request_get_target_system(msg);
    planck_cmd_request->target_component = mavlink_msg_planck_cmd_request_get_target_component(msg);
    planck_cmd_request->type = mavlink_msg_planck_cmd_request_get_type(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_PLANCK_CMD_REQUEST_LEN? msg->len : MAVLINK_MSG_ID_PLANCK_CMD_REQUEST_LEN;
        memset(planck_cmd_request, 0, MAVLINK_MSG_ID_PLANCK_CMD_REQUEST_LEN);
    memcpy(planck_cmd_request, _MAV_PAYLOAD(msg), len);
#endif
}
