#include <Arduino.h>
#include <PulsePosition.h>
#include <Wire.h>
#include "IMU.hpp"
PulsePositionInput RC_Input(RISING);

float RC_Values[] = {0, 0, 0, 0, 0, 0, 0, 0};
int CH_Number = 0;

void read_RC(void) {
  CH_Number = RC_Input.available();
  if(CH_Number > 0) {
    for(int i = 1; i <= CH_Number; i++) {
      RC_Values[i - 1] = RC_Input.read(i);
    }
  }
}

IMU imu;
void setup() {
  Serial.println("*** Start IMU (MPU6050) modul. ***");
  Serial.begin(57600);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Wire.setClock(400000);   // Init. clock frequency for I2C as fast mode 
  Wire.begin();            // Init. wire lib and join the I2C bus as peripheral
  delay(250);
  Wire.beginTransmission(MPU6050_DEFAULT_ADDRESS);
  Wire.write(MPU6050_PWR_MGMT_1);
  Wire.write(MPU6050_CLKSEL);
  Wire.endTransmission();
  imu.calibrateGyro(2000);
  // RC_Input.begin(14);
}

void loop() {
  imu.setupGyro();
  imu.displayGyroData();
  /*
  read_RC();
  // Read and display the PPM information on the serial monitor.
  Serial.print("Number of channels: ");
  Serial.print(CH_Number);
  
  Serial.print(" Roll[us]: ");
  Serial.print(RC_Values[0]);
  Serial.print(" Pitch [us]: ");
  Serial.print(RC_Values[1]);
  Serial.print(" Throttle [us]: ");
  Serial.print(RC_Values[2]);
  Serial.print(" Yaw [us]: ");
  Serial.print(RC_Values[3]);
  */
  delay(50);
}
