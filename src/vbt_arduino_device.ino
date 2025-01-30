#include "AccelerationServiceBNO085.h"
#include "BluetoothService.h"
#include "SmoothingService.h"
#include <Wire.h>

AccelerationServiceBNO085 accelerationService;
BluetoothService bluetoothService;
SmoothingService smoothingService;

void setup() {
  Wire.begin();
  Wire.setClock(400000);
  Serial.begin(115200);

  accelerationService.initialize();
  bluetoothService.initialize();
}

BNO085Measurement measurement;
DataPoint smoothedMeasurement;

void loop() {
  if (!accelerationService.isReady()) return;
  if (!bluetoothService.isConnected()) return;
  
  accelerationService.readAcceleration(&measurement);
  if(!smoothingService.smooth(&smoothedMeasurement, DataPoint(measurement.time, measurement.acceleration))) return;
    
  String message = String(smoothedMeasurement.time) + ":" + String(smoothedMeasurement.value);
  bluetoothService.sendAccelerationMessage(message);
}
