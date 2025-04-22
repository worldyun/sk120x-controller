/**
 * @file BLE.cpp
 * @author WorldYun
 * @brief 
 * @version 0.1
 * @date 2025-04-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "BLE.h"
#include "utils/log.h"
#include "BLEWriteData.h"
#include "UserService.h"

// 初始化静态成员变量
BLE* BLE::instance = nullptr;

// 私有构造函数
BLE::BLE() { }

/**
 * @brief 初始化 BLE 服务
 * 
 */
void BLE::init() {
    LOG_INFO("BLE 服务正在初始化");
    if (instance == nullptr) {
        instance = new BLE();
    }
    instance->initBleService();
    instance->initBleCharacteristic();
    instance->start();
    LOG_INFO("BLE 服务初始化完成");
}

/**
 * @brief 启动BleService 并启动广播
 * 
 */
void BLE::start() {
    // 启动服务
    bleService->start();
    // 启动广播
    bleAdvertising = BLEDevice::getAdvertising();
    bleAdvertising->addServiceUUID(CONFIG_BLE_SERVICE_UUID);
    bleAdvertising->setScanResponse(true);
    bleAdvertising->setMinPreferred(0x06); // 设置广告间隔
    bleAdvertising->setMaxPreferred(0x12);
    bleServer->getAdvertising()->start();
}

/**
 * @brief 初始化BLE服务
 * 
 */
void BLE::initBleService() {
    // 初始化BLE
    // 获取BLE地址并设置设备名
    esp_bd_addr_t address;
    esp_read_mac(address, ESP_MAC_BT);
    char deviceName[20];
    snprintf(deviceName, sizeof(deviceName), "%s-%02X%02X", CONFIG_DEVICE_NAME, address[4], address[5]);

    // 初始化BLE设备
    BLEDevice::init(deviceName);
    esp_ble_gap_set_prefered_default_phy(ESP_BLE_GAP_PHY_2M_PREF_MASK, ESP_BLE_GAP_PHY_2M_PREF_MASK);
    BLEDevice::setPower(CONFIG_BLE_POWER_LVL); // 设置BLE功率
    BLEDevice::setMTU(CONFIG_BLE_MTU); // 设置MTU

    // 创建BLE服务器
    bleServer = BLEDevice::createServer();
    bleServer->setCallbacks(new Sk120xBLEServerCallbacks());

    // 创建BLE服务
    bleService = bleServer->createService(CONFIG_BLE_SERVICE_UUID);
}

/**
 * @brief 初始化BLE特征
 * 
 */
void BLE::initBleCharacteristic() {
    ConfigCharacteristicCallbacks* configCharacteristicCallbacks = new ConfigCharacteristicCallbacks();
    // 创建获取所有配置的BLE特征  只读
    getAllConfigCharacteristic = bleService->createCharacteristic(
        CONFIG_BLE_GET_ALL_CONFIG_CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ
    );
    getAllConfigCharacteristic->addDescriptor(new BLE2902());
    getAllConfigCharacteristic->setCallbacks(configCharacteristicCallbacks);
    
    // 创建设置配置的BLE特征
    setConfigCharacteristic = bleService->createCharacteristic(
        CONFIG_BLE_SET_CONFIG_CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_WRITE
    );
    // 注册回调
    setConfigCharacteristic->addDescriptor(new BLE2902());
    setConfigCharacteristic->setCallbacks(configCharacteristicCallbacks);
}

/**
 * @brief 获取BLE实例
 * 
 * @return BLE* 单实例
 */
BLE* BLE::getInstance() {
    return instance;
}

/**
 * @brief 重新开始广播
 * 
 */
void BLE::restartAdvertising() {
    if (bleAdvertising != nullptr && bleServer != nullptr) {
        bleServer->startAdvertising();
    }
}


/**
 * @brief BLEServer onConnect 回调
 * 
 * @param server 
 */
void BLE::Sk120xBLEServerCallbacks::onConnect(BLEServer* server) {
    LOG_INFO("BLE 设备已连接");
}

/**
 * @brief BLEServer onDisconnect 回调
 * 
 * @param server 
 */
void BLE::Sk120xBLEServerCallbacks::onDisconnect(BLEServer* server) {
    LOG_INFO("BLE 连接已断开");
    // 断开连接后开始重新广播
    BLE::getInstance()->restartAdvertising();
}

/**
 * @brief 设置配置的 onWrite 回调
 * 
 * @param characteristic 
 */
void BLE::ConfigCharacteristicCallbacks::onWrite(BLECharacteristic* characteristic) {
    
    LOG_INFO("BLE 配置特征值已写入: %s", characteristic->getData());
    // 解析数据
    BLEWriteData bLEWriteData(characteristic);
    UserService::getInstance()->execFunc(&bLEWriteData); // 执行功能函数
}

/**
 * @brief 获取所有配置的 onRead 回调
 * 
 * @param characteristic 
 */
void BLE::ConfigCharacteristicCallbacks::onRead(BLECharacteristic* characteristic) {
    LOG_INFO("BLE 所有配置特征值已读取");
    characteristic->setValue((uint8_t *)(SKDevice::getInstance()->getSkDeviceModbusRegisters()), sizeof(SkDeviceModbusRegisters));
}