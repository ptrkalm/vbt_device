#include "BluetoothService.h"

BluetoothService::BluetoothService() {}
bool BluetoothService::isDeviceConnected = false;
bool BluetoothService::isOldDeviceConnected = false;

class ServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer *server) {
    BluetoothService::isDeviceConnected = true;
  };

  void onDisconnect(BLEServer *server) {
    BluetoothService::isDeviceConnected = false;
  }
};

void BluetoothService::initialize() {
  BLEDevice::init("VBT Device");
  vbtServer = BLEDevice::createServer();
  vbtServer->setCallbacks(new ServerCallbacks());

  vbtService = vbtServer->createService(VBT_SERVICE_UUID);
  accelerationCharacteristic = vbtService->createCharacteristic(ACCEL_CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_READ |
    BLECharacteristic::PROPERTY_WRITE |
    BLECharacteristic::PROPERTY_NOTIFY |
    BLECharacteristic::PROPERTY_INDICATE);

  vbtService->start();
  vbtServer->getAdvertising()->start();
}

void BluetoothService::sendAccelerationMessage(const String& message) {
  accelerationCharacteristic->setValue(message);
  accelerationCharacteristic->notify();
}

bool BluetoothService::isConnected() {
  if (!isDeviceConnected && isOldDeviceConnected) {
    delay(500);
    vbtServer->startAdvertising();
  }

  if (isDeviceConnected && !isOldDeviceConnected) {
    isOldDeviceConnected = true;
  }

  return isDeviceConnected;
}

