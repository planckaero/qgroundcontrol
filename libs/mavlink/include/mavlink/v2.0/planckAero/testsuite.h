/** @file
 *    @brief MAVLink comm protocol testsuite generated from planckAero.xml
 *    @see http://qgroundcontrol.org/mavlink/
 */
#pragma once
#ifndef PLANCKAERO_TESTSUITE_H
#define PLANCKAERO_TESTSUITE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAVLINK_TEST_ALL
#define MAVLINK_TEST_ALL

static void mavlink_test_planckAero(uint8_t, uint8_t, mavlink_message_t *last_msg);

static void mavlink_test_all(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{

    mavlink_test_planckAero(system_id, component_id, last_msg);
}
#endif




static void mavlink_test_planck_stateinfo(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_PLANCK_STATEINFO >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_planck_stateinfo_t packet_in = {
        93372036854775807ULL,93372036854776311ULL,129.0,157.0,185.0,213.0,241.0,269.0,297.0,325.0,353.0,963500168,963500376,963500584,963500792,963501000,521.0,549.0,577.0,1,68,135,202
    };
    mavlink_planck_stateinfo_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.time_usec = packet_in.time_usec;
        packet1.time_unix_usec = packet_in.time_unix_usec;
        packet1.roll = packet_in.roll;
        packet1.pitch = packet_in.pitch;
        packet1.yaw = packet_in.yaw;
        packet1.gyro_x = packet_in.gyro_x;
        packet1.gyro_y = packet_in.gyro_y;
        packet1.gyro_z = packet_in.gyro_z;
        packet1.xacc = packet_in.xacc;
        packet1.yacc = packet_in.yacc;
        packet1.zacc = packet_in.zacc;
        packet1.lat = packet_in.lat;
        packet1.lon = packet_in.lon;
        packet1.alt = packet_in.alt;
        packet1.relative_alt = packet_in.relative_alt;
        packet1.alt_above_terrain = packet_in.alt_above_terrain;
        packet1.vn = packet_in.vn;
        packet1.ve = packet_in.ve;
        packet1.vd = packet_in.vd;
        packet1.target_system = packet_in.target_system;
        packet1.target_component = packet_in.target_component;
        packet1.mode = packet_in.mode;
        packet1.status = packet_in.status;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_PLANCK_STATEINFO_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_PLANCK_STATEINFO_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_planck_stateinfo_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_planck_stateinfo_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_planck_stateinfo_pack(system_id, component_id, &msg , packet1.target_system , packet1.target_component , packet1.time_usec , packet1.time_unix_usec , packet1.mode , packet1.status , packet1.roll , packet1.pitch , packet1.yaw , packet1.gyro_x , packet1.gyro_y , packet1.gyro_z , packet1.xacc , packet1.yacc , packet1.zacc , packet1.lat , packet1.lon , packet1.alt , packet1.relative_alt , packet1.alt_above_terrain , packet1.vn , packet1.ve , packet1.vd );
    mavlink_msg_planck_stateinfo_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_planck_stateinfo_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.target_component , packet1.time_usec , packet1.time_unix_usec , packet1.mode , packet1.status , packet1.roll , packet1.pitch , packet1.yaw , packet1.gyro_x , packet1.gyro_y , packet1.gyro_z , packet1.xacc , packet1.yacc , packet1.zacc , packet1.lat , packet1.lon , packet1.alt , packet1.relative_alt , packet1.alt_above_terrain , packet1.vn , packet1.ve , packet1.vd );
    mavlink_msg_planck_stateinfo_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_planck_stateinfo_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_planck_stateinfo_send(MAVLINK_COMM_1 , packet1.target_system , packet1.target_component , packet1.time_usec , packet1.time_unix_usec , packet1.mode , packet1.status , packet1.roll , packet1.pitch , packet1.yaw , packet1.gyro_x , packet1.gyro_y , packet1.gyro_z , packet1.xacc , packet1.yacc , packet1.zacc , packet1.lat , packet1.lon , packet1.alt , packet1.relative_alt , packet1.alt_above_terrain , packet1.vn , packet1.ve , packet1.vd );
    mavlink_msg_planck_stateinfo_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_planck_landing_platform_state(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_planck_landing_platform_state_t packet_in = {
        963497464,963497672,963497880,101.0,129.0,157.0,185.0,213.0,241.0
    };
    mavlink_planck_landing_platform_state_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.latitude = packet_in.latitude;
        packet1.longitude = packet_in.longitude;
        packet1.altitude = packet_in.altitude;
        packet1.vn = packet_in.vn;
        packet1.ve = packet_in.ve;
        packet1.vd = packet_in.vd;
        packet1.roll = packet_in.roll;
        packet1.pitch = packet_in.pitch;
        packet1.yaw = packet_in.yaw;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_PLANCK_LANDING_PLATFORM_STATE_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_planck_landing_platform_state_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_planck_landing_platform_state_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_planck_landing_platform_state_pack(system_id, component_id, &msg , packet1.latitude , packet1.longitude , packet1.altitude , packet1.vn , packet1.ve , packet1.vd , packet1.roll , packet1.pitch , packet1.yaw );
    mavlink_msg_planck_landing_platform_state_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_planck_landing_platform_state_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.latitude , packet1.longitude , packet1.altitude , packet1.vn , packet1.ve , packet1.vd , packet1.roll , packet1.pitch , packet1.yaw );
    mavlink_msg_planck_landing_platform_state_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_planck_landing_platform_state_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_planck_landing_platform_state_send(MAVLINK_COMM_1 , packet1.latitude , packet1.longitude , packet1.altitude , packet1.vn , packet1.ve , packet1.vd , packet1.roll , packet1.pitch , packet1.yaw );
    mavlink_msg_planck_landing_platform_state_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_planck_status(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_PLANCK_STATUS >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_planck_status_t packet_in = {
        5,72,139,206,17,84,151,218
    };
    mavlink_planck_status_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.target_system = packet_in.target_system;
        packet1.target_component = packet_in.target_component;
        packet1.status = packet_in.status;
        packet1.failsafe = packet_in.failsafe;
        packet1.takeoff_ready = packet_in.takeoff_ready;
        packet1.land_ready = packet_in.land_ready;
        packet1.takeoff_complete = packet_in.takeoff_complete;
        packet1.at_location = packet_in.at_location;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_PLANCK_STATUS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_PLANCK_STATUS_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_planck_status_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_planck_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_planck_status_pack(system_id, component_id, &msg , packet1.target_system , packet1.target_component , packet1.status , packet1.failsafe , packet1.takeoff_ready , packet1.land_ready , packet1.takeoff_complete , packet1.at_location );
    mavlink_msg_planck_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_planck_status_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.target_component , packet1.status , packet1.failsafe , packet1.takeoff_ready , packet1.land_ready , packet1.takeoff_complete , packet1.at_location );
    mavlink_msg_planck_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_planck_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_planck_status_send(MAVLINK_COMM_1 , packet1.target_system , packet1.target_component , packet1.status , packet1.failsafe , packet1.takeoff_ready , packet1.land_ready , packet1.takeoff_complete , packet1.at_location );
    mavlink_msg_planck_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_planck_cmd_msg(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_PLANCK_CMD_MSG >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_planck_cmd_msg_t packet_in = {
        963497464,963497672,73.0,{ 101.0, 102.0, 103.0 },{ 185.0, 186.0, 187.0 },{ 269.0, 270.0, 271.0 },19731,27,94,161
    };
    mavlink_planck_cmd_msg_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.lat = packet_in.lat;
        packet1.lon = packet_in.lon;
        packet1.alt = packet_in.alt;
        packet1.type_mask = packet_in.type_mask;
        packet1.target_system = packet_in.target_system;
        packet1.target_component = packet_in.target_component;
        packet1.frame = packet_in.frame;
        
        mav_array_memcpy(packet1.vel, packet_in.vel, sizeof(float)*3);
        mav_array_memcpy(packet1.acc, packet_in.acc, sizeof(float)*3);
        mav_array_memcpy(packet1.att, packet_in.att, sizeof(float)*3);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_PLANCK_CMD_MSG_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_PLANCK_CMD_MSG_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_planck_cmd_msg_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_planck_cmd_msg_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_planck_cmd_msg_pack(system_id, component_id, &msg , packet1.target_system , packet1.target_component , packet1.frame , packet1.type_mask , packet1.lat , packet1.lon , packet1.alt , packet1.vel , packet1.acc , packet1.att );
    mavlink_msg_planck_cmd_msg_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_planck_cmd_msg_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.target_component , packet1.frame , packet1.type_mask , packet1.lat , packet1.lon , packet1.alt , packet1.vel , packet1.acc , packet1.att );
    mavlink_msg_planck_cmd_msg_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_planck_cmd_msg_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_planck_cmd_msg_send(MAVLINK_COMM_1 , packet1.target_system , packet1.target_component , packet1.frame , packet1.type_mask , packet1.lat , packet1.lon , packet1.alt , packet1.vel , packet1.acc , packet1.att );
    mavlink_msg_planck_cmd_msg_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_planck_cmd_request(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_PLANCK_CMD_REQUEST >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_planck_cmd_request_t packet_in = {
        17.0,45.0,73.0,101.0,129.0,157.0,77,144,211
    };
    mavlink_planck_cmd_request_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.param1 = packet_in.param1;
        packet1.param2 = packet_in.param2;
        packet1.param3 = packet_in.param3;
        packet1.param4 = packet_in.param4;
        packet1.param5 = packet_in.param5;
        packet1.param6 = packet_in.param6;
        packet1.target_system = packet_in.target_system;
        packet1.target_component = packet_in.target_component;
        packet1.type = packet_in.type;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_PLANCK_CMD_REQUEST_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_PLANCK_CMD_REQUEST_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_planck_cmd_request_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_planck_cmd_request_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_planck_cmd_request_pack(system_id, component_id, &msg , packet1.target_system , packet1.target_component , packet1.type , packet1.param1 , packet1.param2 , packet1.param3 , packet1.param4 , packet1.param5 , packet1.param6 );
    mavlink_msg_planck_cmd_request_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_planck_cmd_request_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.target_component , packet1.type , packet1.param1 , packet1.param2 , packet1.param3 , packet1.param4 , packet1.param5 , packet1.param6 );
    mavlink_msg_planck_cmd_request_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_planck_cmd_request_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_planck_cmd_request_send(MAVLINK_COMM_1 , packet1.target_system , packet1.target_component , packet1.type , packet1.param1 , packet1.param2 , packet1.param3 , packet1.param4 , packet1.param5 , packet1.param6 );
    mavlink_msg_planck_cmd_request_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_planck_landing_tag_estimate_ned(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_planck_landing_tag_estimate_ned_t packet_in = {
        93372036854775807ULL,963497880,101.0,129.0,157.0,185.0,213.0,241.0,269.0,297.0,325.0,149,216
    };
    mavlink_planck_landing_tag_estimate_ned_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.ap_timestamp_us = packet_in.ap_timestamp_us;
        packet1.age = packet_in.age;
        packet1.x = packet_in.x;
        packet1.y = packet_in.y;
        packet1.z = packet_in.z;
        packet1.vx = packet_in.vx;
        packet1.vy = packet_in.vy;
        packet1.vz = packet_in.vz;
        packet1.roll = packet_in.roll;
        packet1.pitch = packet_in.pitch;
        packet1.yaw = packet_in.yaw;
        packet1.target_system = packet_in.target_system;
        packet1.target_component = packet_in.target_component;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_NED_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_planck_landing_tag_estimate_ned_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_planck_landing_tag_estimate_ned_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_planck_landing_tag_estimate_ned_pack(system_id, component_id, &msg , packet1.target_system , packet1.target_component , packet1.age , packet1.ap_timestamp_us , packet1.x , packet1.y , packet1.z , packet1.vx , packet1.vy , packet1.vz , packet1.roll , packet1.pitch , packet1.yaw );
    mavlink_msg_planck_landing_tag_estimate_ned_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_planck_landing_tag_estimate_ned_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.target_component , packet1.age , packet1.ap_timestamp_us , packet1.x , packet1.y , packet1.z , packet1.vx , packet1.vy , packet1.vz , packet1.roll , packet1.pitch , packet1.yaw );
    mavlink_msg_planck_landing_tag_estimate_ned_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_planck_landing_tag_estimate_ned_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_planck_landing_tag_estimate_ned_send(MAVLINK_COMM_1 , packet1.target_system , packet1.target_component , packet1.age , packet1.ap_timestamp_us , packet1.x , packet1.y , packet1.z , packet1.vx , packet1.vy , packet1.vz , packet1.roll , packet1.pitch , packet1.yaw );
    mavlink_msg_planck_landing_tag_estimate_ned_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_planck_landing_tag_measurement_body(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_planck_landing_tag_measurement_body_t packet_in = {
        93372036854775807ULL,963497880,101.0,129.0,157.0,185.0,213.0,241.0,113,180
    };
    mavlink_planck_landing_tag_measurement_body_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.ap_timestamp_us = packet_in.ap_timestamp_us;
        packet1.age = packet_in.age;
        packet1.x = packet_in.x;
        packet1.y = packet_in.y;
        packet1.z = packet_in.z;
        packet1.roll = packet_in.roll;
        packet1.pitch = packet_in.pitch;
        packet1.yaw = packet_in.yaw;
        packet1.target_system = packet_in.target_system;
        packet1.target_component = packet_in.target_component;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_PLANCK_LANDING_TAG_MEASUREMENT_BODY_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_planck_landing_tag_measurement_body_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_planck_landing_tag_measurement_body_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_planck_landing_tag_measurement_body_pack(system_id, component_id, &msg , packet1.target_system , packet1.target_component , packet1.age , packet1.ap_timestamp_us , packet1.x , packet1.y , packet1.z , packet1.roll , packet1.pitch , packet1.yaw );
    mavlink_msg_planck_landing_tag_measurement_body_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_planck_landing_tag_measurement_body_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.target_component , packet1.age , packet1.ap_timestamp_us , packet1.x , packet1.y , packet1.z , packet1.roll , packet1.pitch , packet1.yaw );
    mavlink_msg_planck_landing_tag_measurement_body_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_planck_landing_tag_measurement_body_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_planck_landing_tag_measurement_body_send(MAVLINK_COMM_1 , packet1.target_system , packet1.target_component , packet1.age , packet1.ap_timestamp_us , packet1.x , packet1.y , packet1.z , packet1.roll , packet1.pitch , packet1.yaw );
    mavlink_msg_planck_landing_tag_measurement_body_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_planck_landing_tag_estimate_gps(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_planck_landing_tag_estimate_gps_t packet_in = {
        963497464,963497672,73.0,101.0,129.0,157.0,77,144
    };
    mavlink_planck_landing_tag_estimate_gps_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.lat = packet_in.lat;
        packet1.lon = packet_in.lon;
        packet1.alt = packet_in.alt;
        packet1.vx = packet_in.vx;
        packet1.vy = packet_in.vy;
        packet1.vz = packet_in.vz;
        packet1.target_system = packet_in.target_system;
        packet1.target_component = packet_in.target_component;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_PLANCK_LANDING_TAG_ESTIMATE_GPS_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_planck_landing_tag_estimate_gps_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_planck_landing_tag_estimate_gps_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_planck_landing_tag_estimate_gps_pack(system_id, component_id, &msg , packet1.target_system , packet1.target_component , packet1.lat , packet1.lon , packet1.alt , packet1.vx , packet1.vy , packet1.vz );
    mavlink_msg_planck_landing_tag_estimate_gps_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_planck_landing_tag_estimate_gps_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.target_component , packet1.lat , packet1.lon , packet1.alt , packet1.vx , packet1.vy , packet1.vz );
    mavlink_msg_planck_landing_tag_estimate_gps_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_planck_landing_tag_estimate_gps_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_planck_landing_tag_estimate_gps_send(MAVLINK_COMM_1 , packet1.target_system , packet1.target_component , packet1.lat , packet1.lon , packet1.alt , packet1.vx , packet1.vy , packet1.vz );
    mavlink_msg_planck_landing_tag_estimate_gps_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_planckAero(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_planck_stateinfo(system_id, component_id, last_msg);
    mavlink_test_planck_landing_platform_state(system_id, component_id, last_msg);
    mavlink_test_planck_status(system_id, component_id, last_msg);
    mavlink_test_planck_cmd_msg(system_id, component_id, last_msg);
    mavlink_test_planck_cmd_request(system_id, component_id, last_msg);
    mavlink_test_planck_landing_tag_estimate_ned(system_id, component_id, last_msg);
    mavlink_test_planck_landing_tag_measurement_body(system_id, component_id, last_msg);
    mavlink_test_planck_landing_tag_estimate_gps(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // PLANCKAERO_TESTSUITE_H
