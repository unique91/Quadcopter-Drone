/**
 * @file IMU.hpp
 * @author Johannes Saldan
 * @version 1.0
 */

#ifndef _QUADROCOPTER_DRONE_IMU_HPP_
#define _QUADROCOPTER_DRONE_IMU_HPP_

#include "Arduino.h"

/**
 * Hardware pin setup:
 *  +------------+------------+
 *  | Teensy 4.0 |   MPU6050  |
 *  +------------+------------+
 *  |    5.0V    |    VCC     |
 *  +------------+------------+
 *  |    GND     |    GND     |
 *  +------------+------------+
 *  |    P19     |    SCL     |
 *  +------------+------------+
 *  |    P18     |    SDA     |
 *  +------------+------------+
 */

#define MPU6050_CLKSEL       (0x00)     // Internal 8MHz oscillator
#define MPU6050_DLPF_CFG     (0x05)     // Configured the DLPF settig
#define MPU6050_FS_SEL       (0x8)      // Gyroscope full scale definition (set Bit3)
#define MPU6050_CONFIG       (0x1A)     // Configuration for Digital Low Pass Filter (DLPF)
#define MPU6050_GYRO_CONFIG  (0x1B)     // Configuration for gyroscope measurements
#define MPU6050_GYRO_XOUT_H  (0x43)     // Gyroscope data
#define MPU6050_PWR_MGMT_1   (0x6B)     // Configuration for power mode and clock source


#define MPU6050_DEFAULT_ADDRESS  (0x68)     // Default I2C address of MPU6050 
#define MPU6050_WHO_AM_I         (0x75)     // Verify the identity of the device. Contains address of the sensor(0x68)

// Constant value to convert raw gyroscope to degree/s
#define MPU6050_GYRO_FACTOR_500  (1.0/65.5)   

struct Vector
{
    float x;   // Roll around x-axis
    float y;   // Pitch around y-axis
    float z;   // Yaw around z-axis
};

class IMU
{
    public:
        IMU();
        ~IMU();

    void setupGyro();
    void calibrateGyro(uint16_t samples = 50);
    void displayGyroData();

    private:
        Vector gyroData;
        float gyro_x, gyro_y, gyro_z;      // Rotation in roll, pith and yaw angle
        float accel_x, accel_y, accel_z;
        float calib_x, calib_y, calib_z;
};

#endif