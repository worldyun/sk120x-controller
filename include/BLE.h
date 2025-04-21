#include <Arduino.h>
#include "config.h"
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

class BLE {
public:
    // 静态方法，用于初始化 BLE 服务
    static void init();
    void restartAdvertising();
    // 静态方法，用于获取 BLE 实例
    static BLE* getInstance();

private:
    BLE();
    static BLE* instance;
    BLEServer* bleServer;
    BLEService* bleService;
    BLECharacteristic* getAllConfigCharacteristic;
    BLECharacteristic* setConfigCharacteristic;
    BLEAdvertising* bleAdvertising;

    void start();
    void initBleService();
    void initBleCharacteristic();

    class Sk120xBLEServerCallbacks : public BLEServerCallbacks {
        void onConnect(BLEServer* pServer) override;
        void onDisconnect(BLEServer* pServer) override;
    };

    class ConfigCharacteristicCallbacks : public BLECharacteristicCallbacks {
        void onWrite(BLECharacteristic* pCharacteristic) override;
        void onRead(BLECharacteristic* pCharacteristic) override;
    };
};
