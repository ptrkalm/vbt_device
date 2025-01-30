#ifndef BLUETOOTH_SERVICE_H
#define BLUETOOTH_SERVICE_H

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define VBT_SERVICE_UUID                "fbd477dd-d0c8-484a-b288-632366d17750"
#define ACCEL_CHARACTERISTIC_UUID       "fbd7ca0a-1d3f-4563-b4c7-6323802840d1"

class BluetoothService {
public:
    BluetoothService();
    void initialize();
    void sendAccelerationMessage(const String& message);
    bool isConnected();

    static bool isDeviceConnected;
    static bool isOldDeviceConnected;

private:
    BLEServer* vbtServer;
    BLEService* vbtService;
    BLECharacteristic* accelerationCharacteristic;
};

#endif