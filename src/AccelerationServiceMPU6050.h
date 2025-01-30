#ifndef ACCELERATION_SERVICE_MPU6050_H
#define ACCELERATION_SERVICE_MPU6050_H

#include <cstdint>
#include "MPU6050_6Axis_MotionApps20.h"

struct MPU6050Measurement {
  float time;
  float acceleration;
};

class AccelerationServiceMPU6050 {
  public:
    AccelerationServiceMPU6050();
    void initialize();
    bool readAcceleration(MPU6050Measurement *measurement);
    bool isReady();

  private:
    MPU6050 mpu;
    bool isDMPReady;
    uint8_t devStatus;
    uint8_t FIFOBuffer[64];

    Quaternion quaternion;
    VectorFloat gravity;
    VectorInt16 accel;
    VectorInt16 linearAccel;
    VectorInt16 worldLinearAccel;
};

#endif