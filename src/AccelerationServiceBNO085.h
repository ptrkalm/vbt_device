#ifndef ACCELERATION_SERVICE_BNO085_H
#define ACCELERATION_SERVICE_BNO085_H

#include <Adafruit_BNO08x.h>

struct BNO085Measurement {
  float time;
  float acceleration;
};

class AccelerationServiceBNO085 {
  public:
    AccelerationServiceBNO085();
    void initialize();
    void readAcceleration(BNO085Measurement *measurement);
    bool isReady();

  private:
    Adafruit_BNO08x bno;
    sh2_SensorValue_t event;
    bool isBNOReady;
};

#endif