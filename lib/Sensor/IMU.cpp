/**
 * @file IMU.hpp
 * @author Johannes Saldan
 * @version 1.0
 */

#include "IMU.hpp"
#include <Wire.h>

IMU::IMU()
{

}

IMU::~IMU()
{

}

void IMU::setupGyro()
{
    Wire.beginTransmission(MPU6050_DEFAULT_ADDRESS);   // Start transmitting to address (0x68)
    Wire.write(MPU6050_CONFIG);                        // Sends value (0x1A)
    Wire.write(MPU6050_DLPF_CFG);
    Wire.endTransmission();                            // Stop transmitting

    Wire.beginTransmission(MPU6050_DEFAULT_ADDRESS);
    Wire.write(MPU6050_GYRO_CONFIG);
    Wire.write(MPU6050_FS_SEL);
    Wire.endTransmission();

    Wire.beginTransmission(MPU6050_DEFAULT_ADDRESS);
    Wire.write(MPU6050_GYRO_XOUT_H);
    Wire.endTransmission();

    Wire.requestFrom(MPU6050_DEFAULT_ADDRESS, 6);
    gyro_x = (int16_t)(Wire.read() << 8 | Wire.read()) / 65.5f; 
    gyro_y = (int16_t)(Wire.read() << 8 | Wire.read()) / 65.5f;
    gyro_z = (int16_t)(Wire.read() << 8 | Wire.read()) / 65.5f; 
}

void IMU::calibrateGyro(uint16_t samples)
{
    for(int sample = 0; sample < samples; sample++)
    {
        setupGyro();
        calib_x += gyro_x;
        calib_y += gyro_y;
        calib_z += gyro_z;
    }
    calib_x /= samples;
    calib_y /= samples;
    calib_z /= samples;
}

void IMU::displayGyroData()
{
    gyro_x -= calib_x;
    gyro_y -= calib_y;
    gyro_z -= calib_z;

    Serial.print("Roll rate [°/s]= ");
    Serial.print(gyro_x);
    Serial.print(" Pitch Rate [°/s]= ");
    Serial.print(gyro_y);
    Serial.print(" Yaw Rate [°/s]= ");
    Serial.println(gyro_z);
}
