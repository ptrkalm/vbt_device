#include "AccelerationServiceMPU6050.h"
#include <Arduino.h>

#define G 9.80665

AccelerationServiceMPU6050::AccelerationServiceMPU6050() {
    isDMPReady = false;
}

void AccelerationServiceMPU6050::initialize() {
  isDMPReady = false;
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed");
    return;
  }

  devStatus = mpu.dmpInitialize();

  if (devStatus == 0) {
    Serial.println("Calibrating accelerometer...");
    mpu.CalibrateAccel(50);
    Serial.println("Calibrated accelerometer.");

    Serial.println("Calibrating gyroscope at first position...");
    mpu.CalibrateGyro(50);
    Serial.println("Calibrated gyroscope.");

    Serial.println("These are the Active offsets: ");
    mpu.PrintActiveOffsets();

    Serial.println(F("Enabling DMP..."));
    mpu.setDMPEnabled(true);
    isDMPReady = true;

    Serial.println("DMP initialization successful");
  } else {
    Serial.println("DMP initialization failed");
  }  
}

bool AccelerationServiceMPU6050::readAcceleration(MPU6050Measurement *measurement) {
  if (!mpu.dmpGetCurrentFIFOPacket(FIFOBuffer)) return false;
  measurement->time = float(millis()) / 1000;
  
  mpu.dmpGetQuaternion(&quaternion, FIFOBuffer);
  mpu.dmpGetAccel(&accel, FIFOBuffer);
  mpu.dmpGetGravity(&gravity, &quaternion);
  mpu.dmpGetLinearAccel(&linearAccel, &accel, &gravity);
  
  measurement->acceleration = float(linearAccel.z) * G / 8192;
  return true;
}

bool AccelerationServiceMPU6050::isReady() {
  return isDMPReady;
}