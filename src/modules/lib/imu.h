/**
 * The IMU module is responsible for orientation determination 
 * and acts as an Attitude Heading Reference System (AHRS)
 *
 * We will use quaternion based Kalman filtering to fuse 
 * Magnetometer, Accelerometer, and Rate Gyroscope (MARG) data into 
 * clean (low-bias) attitude/heading information.
 */

#ifndef _IMU_H_
#define _IMU_H_

float g_x, g_y, g_z;
float a_x, a_y, a_z;
float m_x, m_y, m_z;

/* Update the current state using Kalman state estimation filter */
void update_filter(float, float, float, float, float, float, float, float, float);

#endif
