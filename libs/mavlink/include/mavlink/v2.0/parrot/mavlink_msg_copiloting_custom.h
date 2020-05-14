#pragma once
// MESSAGE COPILOTING_CUSTOM PACKING

#define MAVLINK_MSG_ID_COPILOTING_CUSTOM 40001

MAVPACKED(
typedef struct __mavlink_copiloting_custom_t {
 uint32_t len; /*< [bytes] Data length.*/
 uint8_t data[128]; /*<  Raw data.*/
}) mavlink_copiloting_custom_t;

#define MAVLINK_MSG_ID_COPILOTING_CUSTOM_LEN 132
#define MAVLINK_MSG_ID_COPILOTING_CUSTOM_MIN_LEN 132
#define MAVLINK_MSG_ID_40001_LEN 132
#define MAVLINK_MSG_ID_40001_MIN_LEN 132

#define MAVLINK_MSG_ID_COPILOTING_CUSTOM_CRC 190
#define MAVLINK_MSG_ID_40001_CRC 190

#define MAVLINK_MSG_COPILOTING_CUSTOM_FIELD_DATA_LEN 128

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_COPILOTING_CUSTOM { \
    40001, \
    "COPILOTING_CUSTOM", \
    2, \
    {  { "len", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_copiloting_custom_t, len) }, \
         { "data", NULL, MAVLINK_TYPE_UINT8_T, 128, 4, offsetof(mavlink_copiloting_custom_t, data) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_COPILOTING_CUSTOM { \
    "COPILOTING_CUSTOM", \
    2, \
    {  { "len", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_copiloting_custom_t, len) }, \
         { "data", NULL, MAVLINK_TYPE_UINT8_T, 128, 4, offsetof(mavlink_copiloting_custom_t, data) }, \
         } \
}
#endif

/**
 * @brief Pack a copiloting_custom message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param len [bytes] Data length.
 * @param data  Raw data.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_copiloting_custom_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t len, const uint8_t *data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_COPILOTING_CUSTOM_LEN];
    _mav_put_uint32_t(buf, 0, len);
    _mav_put_uint8_t_array(buf, 4, data, 128);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_COPILOTING_CUSTOM_LEN);
#else
    mavlink_copiloting_custom_t packet;
    packet.len = len;
    mav_array_memcpy(packet.data, data, sizeof(uint8_t)*128);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_COPILOTING_CUSTOM_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_COPILOTING_CUSTOM;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_COPILOTING_CUSTOM_MIN_LEN, MAVLINK_MSG_ID_COPILOTING_CUSTOM_LEN, MAVLINK_MSG_ID_COPILOTING_CUSTOM_CRC);
}

/**
 * @brief Pack a copiloting_custom message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param len [bytes] Data length.
 * @param data  Raw data.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_copiloting_custom_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t len,const uint8_t *data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_COPILOTING_CUSTOM_LEN];
    _mav_put_uint32_t(buf, 0, len);
    _mav_put_uint8_t_array(buf, 4, data, 128);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_COPILOTING_CUSTOM_LEN);
#else
    mavlink_copiloting_custom_t packet;
    packet.len = len;
    mav_array_memcpy(packet.data, data, sizeof(uint8_t)*128);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_COPILOTING_CUSTOM_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_COPILOTING_CUSTOM;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_COPILOTING_CUSTOM_MIN_LEN, MAVLINK_MSG_ID_COPILOTING_CUSTOM_LEN, MAVLINK_MSG_ID_COPILOTING_CUSTOM_CRC);
}

/**
 * @brief Encode a copiloting_custom struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param copiloting_custom C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_copiloting_custom_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_copiloting_custom_t* copiloting_custom)
{
    return mavlink_msg_copiloting_custom_pack(system_id, component_id, msg, copiloting_custom->len, copiloting_custom->data);
}

/**
 * @brief Encode a copiloting_custom struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param copiloting_custom C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_copiloting_custom_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_copiloting_custom_t* copiloting_custom)
{
    return mavlink_msg_copiloting_custom_pack_chan(system_id, component_id, chan, msg, copiloting_custom->len, copiloting_custom->data);
}

/**
 * @brief Send a copiloting_custom message
 * @param chan MAVLink channel to send the message
 *
 * @param len [bytes] Data length.
 * @param data  Raw data.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_copiloting_custom_send(mavlink_channel_t chan, uint32_t len, const uint8_t *data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_COPILOTING_CUSTOM_LEN];
    _mav_put_uint32_t(buf, 0, len);
    _mav_put_uint8_t_array(buf, 4, data, 128);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COPILOTING_CUSTOM, buf, MAVLINK_MSG_ID_COPILOTING_CUSTOM_MIN_LEN, MAVLINK_MSG_ID_COPILOTING_CUSTOM_LEN, MAVLINK_MSG_ID_COPILOTING_CUSTOM_CRC);
#else
    mavlink_copiloting_custom_t packet;
    packet.len = len;
    mav_array_memcpy(packet.data, data, sizeof(uint8_t)*128);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COPILOTING_CUSTOM, (const char *)&packet, MAVLINK_MSG_ID_COPILOTING_CUSTOM_MIN_LEN, MAVLINK_MSG_ID_COPILOTING_CUSTOM_LEN, MAVLINK_MSG_ID_COPILOTING_CUSTOM_CRC);
#endif
}

/**
 * @brief Send a copiloting_custom message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_copiloting_custom_send_struct(mavlink_channel_t chan, const mavlink_copiloting_custom_t* copiloting_custom)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_copiloting_custom_send(chan, copiloting_custom->len, copiloting_custom->data);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COPILOTING_CUSTOM, (const char *)copiloting_custom, MAVLINK_MSG_ID_COPILOTING_CUSTOM_MIN_LEN, MAVLINK_MSG_ID_COPILOTING_CUSTOM_LEN, MAVLINK_MSG_ID_COPILOTING_CUSTOM_CRC);
#endif
}

#if MAVLINK_MSG_ID_COPILOTING_CUSTOM_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_copiloting_custom_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t len, const uint8_t *data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, len);
    _mav_put_uint8_t_array(buf, 4, data, 128);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COPILOTING_CUSTOM, buf, MAVLINK_MSG_ID_COPILOTING_CUSTOM_MIN_LEN, MAVLINK_MSG_ID_COPILOTING_CUSTOM_LEN, MAVLINK_MSG_ID_COPILOTING_CUSTOM_CRC);
#else
    mavlink_copiloting_custom_t *packet = (mavlink_copiloting_custom_t *)msgbuf;
    packet->len = len;
    mav_array_memcpy(packet->data, data, sizeof(uint8_t)*128);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COPILOTING_CUSTOM, (const char *)packet, MAVLINK_MSG_ID_COPILOTING_CUSTOM_MIN_LEN, MAVLINK_MSG_ID_COPILOTING_CUSTOM_LEN, MAVLINK_MSG_ID_COPILOTING_CUSTOM_CRC);
#endif
}
#endif

#endif

// MESSAGE COPILOTING_CUSTOM UNPACKING


/**
 * @brief Get field len from copiloting_custom message
 *
 * @return [bytes] Data length.
 */
static inline uint32_t mavlink_msg_copiloting_custom_get_len(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field data from copiloting_custom message
 *
 * @return  Raw data.
 */
static inline uint16_t mavlink_msg_copiloting_custom_get_data(const mavlink_message_t* msg, uint8_t *data)
{
    return _MAV_RETURN_uint8_t_array(msg, data, 128,  4);
}

/**
 * @brief Decode a copiloting_custom message into a struct
 *
 * @param msg The message to decode
 * @param copiloting_custom C-struct to decode the message contents into
 */
static inline void mavlink_msg_copiloting_custom_decode(const mavlink_message_t* msg, mavlink_copiloting_custom_t* copiloting_custom)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    copiloting_custom->len = mavlink_msg_copiloting_custom_get_len(msg);
    mavlink_msg_copiloting_custom_get_data(msg, copiloting_custom->data);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_COPILOTING_CUSTOM_LEN? msg->len : MAVLINK_MSG_ID_COPILOTING_CUSTOM_LEN;
        memset(copiloting_custom, 0, MAVLINK_MSG_ID_COPILOTING_CUSTOM_LEN);
    memcpy(copiloting_custom, _MAV_PAYLOAD(msg), len);
#endif
}
