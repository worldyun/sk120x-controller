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
    //创建一个每秒执行的通知任务
    xTaskCreate(
        [](void* param) {
            BLE* ble = static_cast<BLE*>(param);
            uint8_t data[CONFIG_BLE_NOTIFY_TOP10_REG_SIZE] = {0}; // 用于存储读取的寄存器数据
            while (true) {
                // 发送通知
                if ( ble->bleServer->getConnectedCount() > 0 
                        && ble->notifyTop10RegCharacteristic != nullptr 
                        && ble->isConnected 
                        && SKDevice::getInstance() != nullptr 
                        && SKDevice::getInstance()->isInited) {
                    // 复制寄存器数据到data数组
                    memcpy(data, SKDevice::getInstance()->getSkDeviceModbusRegisters(), CONFIG_BLE_NOTIFY_TOP10_REG_SIZE);
                    // 将输出使能放在输出瓦时高2字节的首位
                    data[15] &= 0x7F; // 清除首位
                    data[15] |= (SKDevice::getInstance()->getSkDeviceModbusRegisters()->outEnable << 7);
                    ble->notifyTop10RegCharacteristic->setValue(data, CONFIG_BLE_NOTIFY_TOP10_REG_SIZE);
                    ble->notifyTop10RegCharacteristic->notify(); // 发送通知
                }
                vTaskDelay(pdMS_TO_TICKS(CONFIG_BLE_NOTIFY_TOP10_REG_INTERVAL));
            }
        },
        "BLENotifyTask",
        CONFIG_TASK_STACK_SIZE,
        this,
        1,
        nullptr
    );
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
    // 创建获取所有配置的BLE特征  只读
    getAllConfigCharacteristic = bleService->createCharacteristic(
        CONFIG_BLE_GET_ALL_CONFIG_CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ
    );
    getAllConfigCharacteristic->addDescriptor(new BLE2902());
    getAllConfigCharacteristic->setCallbacks(new ReadAllConfigCallbacks());
    
    // 创建设置配置的BLE特征
    setConfigCharacteristic = bleService->createCharacteristic(
        CONFIG_BLE_SET_CONFIG_CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_READ
    );

    // 注册回调
    setConfigCharacteristic->addDescriptor(new BLE2902());
    setConfigCharacteristic->setCallbacks(new SetConfigCallbacks());

    // 创建通知特征
    notifyTop10RegCharacteristic = bleService->createCharacteristic(
        CONFIG_BLE_NOTIFY_TOP10_REG_CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_NOTIFY
    );
    notifyTop10RegCharacteristic->addDescriptor(new BLE2902());
    notifyTop10RegCharacteristic->setCallbacks(new NotifyTop10RegCallbacks());
    
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
    BLE::getInstance()->isConnected = true; // 设置连接状态
    LOG_INFO("BLE 设备已连接");
}

/**
 * @brief BLEServer onDisconnect 回调
 * 
 * @param server 
 */
void BLE::Sk120xBLEServerCallbacks::onDisconnect(BLEServer* server) {
    BLE::getInstance()->isConnected = false; // 设置连接状态
    LOG_INFO("BLE 连接已断开");
    // 断开连接后开始重新广播
    BLE::getInstance()->restartAdvertising();
}

/**
 * @brief 设置配置的 onWrite 回调
 * 
 * @param characteristic 
 */
void BLE::SetConfigCallbacks::onWrite(BLECharacteristic* characteristic) {

    LOG_INFO("BLE 配置特征值已写入: %s", characteristic->getData());
    // 解析数据
    BLEWriteData bLEWriteData(characteristic);
    UserService::getInstance()->execFunc(&bLEWriteData, characteristic); // 执行功能函数
}

/**
 * @brief 获取所有配置的 onRead 回调
 * 
 * @param characteristic 
 */
void BLE::ReadAllConfigCallbacks::onRead(BLECharacteristic* characteristic) {
    LOG_INFO("BLE 所有配置特征值已读取");
    // 读取所有配置
    SKDevice::getInstance()->readSkDeviceRegisters(); // 读取寄存器
    characteristic->setValue((uint8_t *)(SKDevice::getInstance()->getSkDeviceModbusRegisters()), sizeof(SkDeviceModbusRegisters));
}


/**
 * @brief 通知前10个寄存器的 onStatus 回调
 * 
 * @param characteristic 
 */
void BLE::NotifyTop10RegCallbacks::onStatus(BLECharacteristic* characteristic, BLECharacteristicCallbacks::Status s, uint32_t code) {
    if (s == BLECharacteristicCallbacks::Status::ERROR_GATT) {
        LOG_ERROR("BLE 通知失败, 重启");
        //重启
        ESP.restart();
    }
}

