#pragma once
// MESSAGE VERSION_QUERY_RESPONSE PACKING

#define MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE 190

MAVPACKED(
typedef struct __mavlink_version_query_response_t {
 uint8_t target_system; /*< System ID*/
 uint8_t target_component; /*< Component ID*/
 uint8_t response; /*< Query or response (QUERY=0, RESPONSE=NON-ZERO)*/
 uint8_t entity; /*< Entity to query/respond (planck-ctrl=0)*/
 int8_t version[40]; /*< NULL-terminated string response with version or N/A for query (max 40 chars including NULL-term)*/
}) mavlink_version_query_response_t;

#define MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE_LEN 44
#define MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE_MIN_LEN 44
#define MAVLINK_MSG_ID_190_LEN 44
#define MAVLINK_MSG_ID_190_MIN_LEN 44

#define MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE_CRC 67
#define MAVLINK_MSG_ID_190_CRC 67

#define MAVLINK_MSG_VERSION_QUERY_RESPONSE_FIELD_VERSION_LEN 40

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_VERSION_QUERY_RESPONSE { \
    190, \
    "VERSION_QUERY_RESPONSE", \
    5, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_version_query_response_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_version_query_response_t, target_component) }, \
         { "response", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_version_query_response_t, response) }, \
         { "entity", NULL, MAVLINK_TYPE_UINT8_T, 0, 3, offsetof(mavlink_version_query_response_t, entity) }, \
         { "version", NULL, MAVLINK_TYPE_INT8_T, 40, 4, offsetof(mavlink_version_query_response_t, version) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_VERSION_QUERY_RESPONSE { \
    "VERSION_QUERY_RESPONSE", \
    5, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_version_query_response_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_version_query_response_t, target_component) }, \
         { "response", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_version_query_response_t, response) }, \
         { "entity", NULL, MAVLINK_TYPE_UINT8_T, 0, 3, offsetof(mavlink_version_query_response_t, entity) }, \
         { "version", NULL, MAVLINK_TYPE_INT8_T, 40, 4, offsetof(mavlink_version_query_response_t, version) }, \
         } \
}
#endif

/**
 * @brief Pack a version_query_response message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param response Query or response (QUERY=0, RESPONSE=NON-ZERO)
 * @param entity Entity to query/respond (planck-ctrl=0)
 * @param version NULL-terminated string response with version or N/A for query (max 40 chars including NULL-term)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_version_query_response_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t target_system, uint8_t target_component, uint8_t response, uint8_t entity, const int8_t *version)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE_LEN];
    _mav_put_uint8_t(buf, 0, target_system);
    _mav_put_uint8_t(buf, 1, target_component);
    _mav_put_uint8_t(buf, 2, response);
    _mav_put_uint8_t(buf, 3, entity);
    _mav_put_int8_t_array(buf, 4, version, 40);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE_LEN);
#else
    mavlink_version_query_response_t packet;
    packet.target_system = target_system;
    packet.target_component = target_component;
    packet.response = response;
    packet.entity = entity;
    mav_array_memcpy(packet.version, version, sizeof(int8_t)*40);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE_MIN_LEN, MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE_LEN, MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE_CRC);
}

/**
 * @brief Pack a version_query_response message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system System ID
 * @param target_component Component ID
 * @param response Query or response (QUERY=0, RESPONSE=NON-ZERO)
 * @param entity Entity to query/respond (planck-ctrl=0)
 * @param version NULL-terminated string response with version or N/A for query (max 40 chars including NULL-term)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_version_query_response_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t target_system,uint8_t target_component,uint8_t response,uint8_t entity,const int8_t *version)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE_LEN];
    _mav_put_uint8_t(buf, 0, target_system);
    _mav_put_uint8_t(buf, 1, target_component);
    _mav_put_uint8_t(buf, 2, response);
    _mav_put_uint8_t(buf, 3, entity);
    _mav_put_int8_t_array(buf, 4, version, 40);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE_LEN);
#else
    mavlink_version_query_response_t packet;
    packet.target_system = target_system;
    packet.target_component = target_component;
    packet.response = response;
    packet.entity = entity;
    mav_array_memcpy(packet.version, version, sizeof(int8_t)*40);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE_MIN_LEN, MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE_LEN, MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE_CRC);
}

/**
 * @brief Encode a version_query_response struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param version_query_response C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_version_query_response_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_version_query_response_t* version_query_response)
{
    return mavlink_msg_version_query_response_pack(system_id, component_id, msg, version_query_response->target_system, version_query_response->target_component, version_query_response->response, version_query_response->entity, version_query_response->version);
}

/**
 * @brief Encode a version_query_response struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param version_query_response C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_version_query_response_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_version_query_response_t* version_query_response)
{
    return mavlink_msg_version_query_response_pack_chan(system_id, component_id, chan, msg, version_query_response->target_system, version_query_response->target_component, version_query_response->response, version_query_response->entity, version_query_response->version);
}

/**
 * @brief Send a version_query_response message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param response Query or response (QUERY=0, RESPONSE=NON-ZERO)
 * @param entity Entity to query/respond (planck-ctrl=0)
 * @param version NULL-terminated string response with version or N/A for query (max 40 chars including NULL-term)
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_version_query_response_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, uint8_t response, uint8_t entity, const int8_t *version)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE_LEN];
    _mav_put_uint8_t(buf, 0, target_system);
    _mav_put_uint8_t(buf, 1, target_component);
    _mav_put_uint8_t(buf, 2, response);
    _mav_put_uint8_t(buf, 3, entity);
    _mav_put_int8_t_array(buf, 4, version, 40);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE, buf, MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE_MIN_LEN, MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE_LEN, MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE_CRC);
#else
    mavlink_version_query_response_t packet;
    packet.target_system = target_system;
    packet.target_component = target_component;
    packet.response = response;
    packet.entity = entity;
    mav_array_memcpy(packet.version, version, sizeof(int8_t)*40);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE, (const char *)&packet, MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE_MIN_LEN, MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE_LEN, MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE_CRC);
#endif
}

/**
 * @brief Send a version_query_response message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_version_query_response_send_struct(mavlink_channel_t chan, const mavlink_version_query_response_t* version_query_response)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_version_query_response_send(chan, version_query_response->target_system, version_query_response->target_component, version_query_response->response, version_query_response->entity, version_query_response->version);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE, (const char *)version_query_response, MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE_MIN_LEN, MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE_LEN, MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE_CRC);
#endif
}

#if MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_version_query_response_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t target_system, uint8_t target_component, uint8_t response, uint8_t entity, const int8_t *version)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, target_system);
    _mav_put_uint8_t(buf, 1, target_component);
    _mav_put_uint8_t(buf, 2, response);
    _mav_put_uint8_t(buf, 3, entity);
    _mav_put_int8_t_array(buf, 4, version, 40);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE, buf, MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE_MIN_LEN, MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE_LEN, MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE_CRC);
#else
    mavlink_version_query_response_t *packet = (mavlink_version_query_response_t *)msgbuf;
    packet->target_system = target_system;
    packet->target_component = target_component;
    packet->response = response;
    packet->entity = entity;
    mav_array_memcpy(packet->version, version, sizeof(int8_t)*40);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE, (const char *)packet, MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE_MIN_LEN, MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE_LEN, MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE_CRC);
#endif
}
#endif

#endif

// MESSAGE VERSION_QUERY_RESPONSE UNPACKING


/**
 * @brief Get field target_system from version_query_response message
 *
 * @return System ID
 */
static inline uint8_t mavlink_msg_version_query_response_get_target_system(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field target_component from version_query_response message
 *
 * @return Component ID
 */
static inline uint8_t mavlink_msg_version_query_response_get_target_component(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Get field response from version_query_response message
 *
 * @return Query or response (QUERY=0, RESPONSE=NON-ZERO)
 */
static inline uint8_t mavlink_msg_version_query_response_get_response(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  2);
}

/**
 * @brief Get field entity from version_query_response message
 *
 * @return Entity to query/respond (planck-ctrl=0)
 */
static inline uint8_t mavlink_msg_version_query_response_get_entity(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  3);
}

/**
 * @brief Get field version from version_query_response message
 *
 * @return NULL-terminated string response with version or N/A for query (max 40 chars including NULL-term)
 */
static inline uint16_t mavlink_msg_version_query_response_get_version(const mavlink_message_t* msg, int8_t *version)
{
    return _MAV_RETURN_int8_t_array(msg, version, 40,  4);
}

/**
 * @brief Decode a version_query_response message into a struct
 *
 * @param msg The message to decode
 * @param version_query_response C-struct to decode the message contents into
 */
static inline void mavlink_msg_version_query_response_decode(const mavlink_message_t* msg, mavlink_version_query_response_t* version_query_response)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    version_query_response->target_system = mavlink_msg_version_query_response_get_target_system(msg);
    version_query_response->target_component = mavlink_msg_version_query_response_get_target_component(msg);
    version_query_response->response = mavlink_msg_version_query_response_get_response(msg);
    version_query_response->entity = mavlink_msg_version_query_response_get_entity(msg);
    mavlink_msg_version_query_response_get_version(msg, version_query_response->version);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE_LEN? msg->len : MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE_LEN;
        memset(version_query_response, 0, MAVLINK_MSG_ID_VERSION_QUERY_RESPONSE_LEN);
    memcpy(version_query_response, _MAV_PAYLOAD(msg), len);
#endif
}
