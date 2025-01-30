#include "AccelerationServiceBNO085.h"

AccelerationServiceBNO085::AccelerationServiceBNO085() {
  isBNOReady = false;
}

void AccelerationServiceBNO085::initialize() {
  isBNOReady = false;
  bno = Adafruit_BNO08x();

  while (!bno.begin_I2C()) {
    Serial.println("Failed to find BNO085 chip. Retry in 1 second.");
    delay(1000);
  }
  Serial.println("BNO085 Found!");

  if(!bno.enableReport(SH2_LINEAR_ACCELERATION)) {
    Serial.println("Could not enable ACCELEROMETER report!");
  };
  
  isBNOReady = true;
}

void AccelerationServiceBNO085::readAcceleration(BNO085Measurement *measurement) {
  while(true) {
    if (!bno.getSensorEvent(&event)) continue;
      measurement->time = double(millis()) / 1000;
      measurement->acceleration = event.un.linearAcceleration.z;
      break;
  }
}

bool AccelerationServiceBNO085::isReady() {
  return isBNOReady;
}