/**
 * @file BLE.h
 * @author WorldYun
 * @brief 
 * @version 0.1
 * @date 2025-04-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include <Arduino.h>
#include "config.h"
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "SKDevice.h"

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
    BLEAdvertising* bleAdvertising;
    BLECharacteristic* getAllConfigCharacteristic;
    BLECharacteristic* setConfigCharacteristic;
    BLECharacteristic* notifyTop10RegCharacteristic;
    bool isConnected = false; // 是否连接
    

    void start();
    void initBleService();
    void initBleCharacteristic();

    // BLE 服务器回调类
    class Sk120xBLEServerCallbacks : public BLEServerCallbacks {
        void onConnect(BLEServer* pServer) override;
        void onDisconnect(BLEServer* pServer) override;
    };

    // BLE 特征回调类
    class SetConfigCallbacks : public BLECharacteristicCallbacks {
        void onWrite(BLECharacteristic* pCharacteristic) override;
    };

    //ReadAllConfig回调
    class ReadAllConfigCallbacks : public BLECharacteristicCallbacks {
        void onRead(BLECharacteristic* pCharacteristic) override;
    };
};
