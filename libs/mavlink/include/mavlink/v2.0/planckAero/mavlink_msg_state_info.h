#pragma once
// MESSAGE STATE_INFO PACKING

#define MAVLINK_MSG_ID_STATE_INFO 145

MAVPACKED(
typedef struct __mavlink_state_info_t {
 uint64_t time_usec; /*< Timestamp (micros since boot or Unix epoch)*/
 float roll; /*< Roll angle (rad, -pi..+pi)*/
 float pitch; /*< Pitch angle (rad, -pi..+pi)*/
 float yaw; /*< Yaw angle (rad, -pi..+pi)*/
 int16_t xacc; /*< X acceleration (raw)*/
 int16_t yacc; /*< Y acceleration (raw)*/
 int16_t zacc; /*< Z acceleration (raw)*/
}) mavlink_state_info_t;

#define MAVLINK_MSG_ID_STATE_INFO_LEN 26
#define MAVLINK_MSG_ID_STATE_INFO_MIN_LEN 26
#define MAVLINK_MSG_ID_145_LEN 26
#define MAVLINK_MSG_ID_145_MIN_LEN 26

#define MAVLINK_MSG_ID_STATE_INFO_CRC 107
#define MAVLINK_MSG_ID_145_CRC 107



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_STATE_INFO { \
    145, \
    "STATE_INFO", \
    7, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_state_info_t, time_usec) }, \
         { "roll", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_state_info_t, roll) }, \
         { "pitch", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_state_info_t, pitch) }, \
         { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_state_info_t, yaw) }, \
         { "xacc", NULL, MAVLINK_TYPE_INT16_T, 0, 20, offsetof(mavlink_state_info_t, xacc) }, \
         { "yacc", NULL, MAVLINK_TYPE_INT16_T, 0, 22, offsetof(mavlink_state_info_t, yacc) }, \
         { "zacc", NULL, MAVLINK_TYPE_INT16_T, 0, 24, offsetof(mavlink_state_info_t, zacc) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_STATE_INFO { \
    "STATE_INFO", \
    7, \
    {  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_state_info_t, time_usec) }, \
         { "roll", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_state_info_t, roll) }, \
         { "pitch", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_state_info_t, pitch) }, \
         { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_state_info_t, yaw) }, \
         { "xacc", NULL, MAVLINK_TYPE_INT16_T, 0, 20, offsetof(mavlink_state_info_t, xacc) }, \
         { "yacc", NULL, MAVLINK_TYPE_INT16_T, 0, 22, offsetof(mavlink_state_info_t, yacc) }, \
         { "zacc", NULL, MAVLINK_TYPE_INT16_T, 0, 24, offsetof(mavlink_state_info_t, zacc) }, \
         } \
}
#endif

/**
 * @brief Pack a state_info message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec Timestamp (micros since boot or Unix epoch)
 * @param roll Roll angle (rad, -pi..+pi)
 * @param pitch Pitch angle (rad, -pi..+pi)
 * @param yaw Yaw angle (rad, -pi..+pi)
 * @param xacc X acceleration (raw)
 * @param yacc Y acceleration (raw)
 * @param zacc Z acceleration (raw)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_state_info_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t time_usec, float roll, float pitch, float yaw, int16_t xacc, int16_t yacc, int16_t zacc)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_STATE_INFO_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_float(buf, 8, roll);
    _mav_put_float(buf, 12, pitch);
    _mav_put_float(buf, 16, yaw);
    _mav_put_int16_t(buf, 20, xacc);
    _mav_put_int16_t(buf, 22, yacc);
    _mav_put_int16_t(buf, 24, zacc);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_STATE_INFO_LEN);
#else
    mavlink_state_info_t packet;
    packet.time_usec = time_usec;
    packet.roll = roll;
    packet.pitch = pitch;
    packet.yaw = yaw;
    packet.xacc = xacc;
    packet.yacc = yacc;
    packet.zacc = zacc;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_STATE_INFO_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_STATE_INFO;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_STATE_INFO_MIN_LEN, MAVLINK_MSG_ID_STATE_INFO_LEN, MAVLINK_MSG_ID_STATE_INFO_CRC);
}

/**
 * @brief Pack a state_info message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec Timestamp (micros since boot or Unix epoch)
 * @param roll Roll angle (rad, -pi..+pi)
 * @param pitch Pitch angle (rad, -pi..+pi)
 * @param yaw Yaw angle (rad, -pi..+pi)
 * @param xacc X acceleration (raw)
 * @param yacc Y acceleration (raw)
 * @param zacc Z acceleration (raw)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_state_info_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t time_usec,float roll,float pitch,float yaw,int16_t xacc,int16_t yacc,int16_t zacc)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_STATE_INFO_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_float(buf, 8, roll);
    _mav_put_float(buf, 12, pitch);
    _mav_put_float(buf, 16, yaw);
    _mav_put_int16_t(buf, 20, xacc);
    _mav_put_int16_t(buf, 22, yacc);
    _mav_put_int16_t(buf, 24, zacc);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_STATE_INFO_LEN);
#else
    mavlink_state_info_t packet;
    packet.time_usec = time_usec;
    packet.roll = roll;
    packet.pitch = pitch;
    packet.yaw = yaw;
    packet.xacc = xacc;
    packet.yacc = yacc;
    packet.zacc = zacc;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_STATE_INFO_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_STATE_INFO;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_STATE_INFO_MIN_LEN, MAVLINK_MSG_ID_STATE_INFO_LEN, MAVLINK_MSG_ID_STATE_INFO_CRC);
}

/**
 * @brief Encode a state_info struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param state_info C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_state_info_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_state_info_t* state_info)
{
    return mavlink_msg_state_info_pack(system_id, component_id, msg, state_info->time_usec, state_info->roll, state_info->pitch, state_info->yaw, state_info->xacc, state_info->yacc, state_info->zacc);
}

/**
 * @brief Encode a state_info struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param state_info C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_state_info_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_state_info_t* state_info)
{
    return mavlink_msg_state_info_pack_chan(system_id, component_id, chan, msg, state_info->time_usec, state_info->roll, state_info->pitch, state_info->yaw, state_info->xacc, state_info->yacc, state_info->zacc);
}

/**
 * @brief Send a state_info message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec Timestamp (micros since boot or Unix epoch)
 * @param roll Roll angle (rad, -pi..+pi)
 * @param pitch Pitch angle (rad, -pi..+pi)
 * @param yaw Yaw angle (rad, -pi..+pi)
 * @param xacc X acceleration (raw)
 * @param yacc Y acceleration (raw)
 * @param zacc Z acceleration (raw)
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_state_info_send(mavlink_channel_t chan, uint64_t time_usec, float roll, float pitch, float yaw, int16_t xacc, int16_t yacc, int16_t zacc)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_STATE_INFO_LEN];
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_float(buf, 8, roll);
    _mav_put_float(buf, 12, pitch);
    _mav_put_float(buf, 16, yaw);
    _mav_put_int16_t(buf, 20, xacc);
    _mav_put_int16_t(buf, 22, yacc);
    _mav_put_int16_t(buf, 24, zacc);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STATE_INFO, buf, MAVLINK_MSG_ID_STATE_INFO_MIN_LEN, MAVLINK_MSG_ID_STATE_INFO_LEN, MAVLINK_MSG_ID_STATE_INFO_CRC);
#else
    mavlink_state_info_t packet;
    packet.time_usec = time_usec;
    packet.roll = roll;
    packet.pitch = pitch;
    packet.yaw = yaw;
    packet.xacc = xacc;
    packet.yacc = yacc;
    packet.zacc = zacc;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STATE_INFO, (const char *)&packet, MAVLINK_MSG_ID_STATE_INFO_MIN_LEN, MAVLINK_MSG_ID_STATE_INFO_LEN, MAVLINK_MSG_ID_STATE_INFO_CRC);
#endif
}

/**
 * @brief Send a state_info message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_state_info_send_struct(mavlink_channel_t chan, const mavlink_state_info_t* state_info)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_state_info_send(chan, state_info->time_usec, state_info->roll, state_info->pitch, state_info->yaw, state_info->xacc, state_info->yacc, state_info->zacc);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STATE_INFO, (const char *)state_info, MAVLINK_MSG_ID_STATE_INFO_MIN_LEN, MAVLINK_MSG_ID_STATE_INFO_LEN, MAVLINK_MSG_ID_STATE_INFO_CRC);
#endif
}

#if MAVLINK_MSG_ID_STATE_INFO_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_state_info_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t time_usec, float roll, float pitch, float yaw, int16_t xacc, int16_t yacc, int16_t zacc)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, time_usec);
    _mav_put_float(buf, 8, roll);
    _mav_put_float(buf, 12, pitch);
    _mav_put_float(buf, 16, yaw);
    _mav_put_int16_t(buf, 20, xacc);
    _mav_put_int16_t(buf, 22, yacc);
    _mav_put_int16_t(buf, 24, zacc);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STATE_INFO, buf, MAVLINK_MSG_ID_STATE_INFO_MIN_LEN, MAVLINK_MSG_ID_STATE_INFO_LEN, MAVLINK_MSG_ID_STATE_INFO_CRC);
#else
    mavlink_state_info_t *packet = (mavlink_state_info_t *)msgbuf;
    packet->time_usec = time_usec;
    packet->roll = roll;
    packet->pitch = pitch;
    packet->yaw = yaw;
    packet->xacc = xacc;
    packet->yacc = yacc;
    packet->zacc = zacc;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STATE_INFO, (const char *)packet, MAVLINK_MSG_ID_STATE_INFO_MIN_LEN, MAVLINK_MSG_ID_STATE_INFO_LEN, MAVLINK_MSG_ID_STATE_INFO_CRC);
#endif
}
#endif

#endif

// MESSAGE STATE_INFO UNPACKING


/**
 * @brief Get field time_usec from state_info message
 *
 * @return Timestamp (micros since boot or Unix epoch)
 */
static inline uint64_t mavlink_msg_state_info_get_time_usec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field roll from state_info message
 *
 * @return Roll angle (rad, -pi..+pi)
 */
static inline float mavlink_msg_state_info_get_roll(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field pitch from state_info message
 *
 * @return Pitch angle (rad, -pi..+pi)
 */
static inline float mavlink_msg_state_info_get_pitch(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field yaw from state_info message
 *
 * @return Yaw angle (rad, -pi..+pi)
 */
static inline float mavlink_msg_state_info_get_yaw(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field xacc from state_info message
 *
 * @return X acceleration (raw)
 */
static inline int16_t mavlink_msg_state_info_get_xacc(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  20);
}

/**
 * @brief Get field yacc from state_info message
 *
 * @return Y acceleration (raw)
 */
static inline int16_t mavlink_msg_state_info_get_yacc(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  22);
}

/**
 * @brief Get field zacc from state_info message
 *
 * @return Z acceleration (raw)
 */
static inline int16_t mavlink_msg_state_info_get_zacc(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  24);
}

/**
 * @brief Decode a state_info message into a struct
 *
 * @param msg The message to decode
 * @param state_info C-struct to decode the message contents into
 */
static inline void mavlink_msg_state_info_decode(const mavlink_message_t* msg, mavlink_state_info_t* state_info)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    state_info->time_usec = mavlink_msg_state_info_get_time_usec(msg);
    state_info->roll = mavlink_msg_state_info_get_roll(msg);
    state_info->pitch = mavlink_msg_state_info_get_pitch(msg);
    state_info->yaw = mavlink_msg_state_info_get_yaw(msg);
    state_info->xacc = mavlink_msg_state_info_get_xacc(msg);
    state_info->yacc = mavlink_msg_state_info_get_yacc(msg);
    state_info->zacc = mavlink_msg_state_info_get_zacc(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_STATE_INFO_LEN? msg->len : MAVLINK_MSG_ID_STATE_INFO_LEN;
        memset(state_info, 0, MAVLINK_MSG_ID_STATE_INFO_LEN);
    memcpy(state_info, _MAV_PAYLOAD(msg), len);
#endif
}
