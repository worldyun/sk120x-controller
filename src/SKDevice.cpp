/**
 * @file SKDevice.cpp
 * @author WorldYun
 * @brief 
 * @version 0.1
 * @date 2025-04-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "SKDevice.h"
#include "utils/log.h"

SKDevice* SKDevice::instance = nullptr;


/**
 * @brief 私有构造函数
 * 
 */
SKDevice::SKDevice() { }

/**
 * @brief 私有析构函数
 * 
 */
SKDevice::~SKDevice() {
    if (skModbus != nullptr) {
        delete skModbus;
        skModbus = nullptr;
    }
    if (skDeviceModbusRegisters != nullptr) {
        free(skDeviceModbusRegisters);
        skDeviceModbusRegisters = nullptr;
    }
}

/**
 * @brief 初始化SK设备
 * 
 */
void SKDevice::init() {
    LOG_INFO("SK 设备初始化");
    if (instance == nullptr) {
        instance = new SKDevice();
    }
    instance->initMutex();
    instance->initSKSerialAndModbus();
    instance->initSKDeviceRegisters();
    instance->initTop10RegistersAutoRead();
    instance->isInited = true; // 设置初始化完成标志
    LOG_INFO("SK 设备初始化完成");
}

void SKDevice::initSKSerialAndModbus() {
    LOG_INFO("SK 初始化串口与ModBus");
    Serial1.begin(CONFIG_SK_DEVICE_SERIAL_BAUD_RATE, SERIAL_8N1, CONFIG_SK_DEVICE_SERIAL_RX_PIN, CONFIG_SK_DEVICE_SERIAL_TX_PIN);
    while (!Serial1 && !Serial1.available()){}
    skModbus = new DFRobot_RTU(&Serial1);
    //LOG_INFO("SK 设置ModBus地址 0X%04X", CONFIG_SK_DEVICE_MODBUS_ADDRESS);
    //skModbus->writeHoldingRegister(CONFIG_MODBUS_BROADCAST_ADDRESS, SK_DEVICE_MODBUS_REGISTER_ADDRESS::SK_MODBUS_ID, CONFIG_SK_DEVICE_MODBUS_ADDRESS);
    LOG_INFO("SK 串口与ModBus初始化完成");
}

/**
 * @brief 初始化SK设备寄存器
 * 
 */
void SKDevice::initSKDeviceRegisters() {
    LOG_INFO("SK 初始化设备寄存器");
    //加锁
    xSemaphoreTake(modbusMutex, portMAX_DELAY);
    if (skModbus->readHoldingRegister(CONFIG_SK_DEVICE_MODBUS_ADDRESS, SK_DEVICE_MODBUS_REGISTER_ADDRESS::DEVICE_STATUS) == 1) {
        LOG_INFO("SK 设备未启动");
    } else {
        LOG_INFO("SK 设备已启动");
    }
    //解锁
    xSemaphoreGive(modbusMutex);

    //初始化寄存器对象
    skDeviceModbusRegisters = (SkDeviceModbusRegisters *)malloc(sizeof(SkDeviceModbusRegisters));
    if (skDeviceModbusRegisters == NULL) {
        LOG_ERROR("SK 寄存器内存分配失败，重启中...");
        // 重启
        ESP.restart();
    }
    memset(skDeviceModbusRegisters, 0, sizeof(SkDeviceModbusRegisters));

    // 读取寄存器值
    if (readSkDeviceRegisters() != 0) {
        LOG_ERROR("SK 设备寄存器初始化失败，重启中...");
        // 重启
        ESP.restart();
    }
    LOG_INFO("SK 设备寄存器初始化完成");
    if (CONFIG_LOG_LEVEL >= LOG_LEVEL_INFO) {
        // 打印值以验证
        LOG_INFO("设置电压: %d", skDeviceModbusRegisters->vSet);
        LOG_INFO("设置电流: %d", skDeviceModbusRegisters->iSet);
        LOG_INFO("输出电压: %d", skDeviceModbusRegisters->vOut);
        LOG_INFO("输出电流: %d", skDeviceModbusRegisters->iOut);
        LOG_INFO("输出功率: %d", skDeviceModbusRegisters->wOut);
        LOG_INFO("输入电压: %d", skDeviceModbusRegisters->vIn);
        LOG_INFO("输出安时 (低2字节): %d", skDeviceModbusRegisters->ahOut & 0xFFFF);
        LOG_INFO("输出安时 (高2字节): %d", (skDeviceModbusRegisters->ahOut >> 16) & 0xFFFF);
        LOG_INFO("输出安时: %d", skDeviceModbusRegisters->ahOut);
        LOG_INFO("输出瓦时 (低2字节): %d", skDeviceModbusRegisters->whOut & 0xFFFF);
        LOG_INFO("输出瓦时 (高2字节): %d", (skDeviceModbusRegisters->whOut >> 16) & 0xFFFF);
        LOG_INFO("输出瓦时: %d", skDeviceModbusRegisters->whOut);
        LOG_INFO("输出时间-小时: %d", skDeviceModbusRegisters->hOut);
        LOG_INFO("输出时间-分钟: %d", skDeviceModbusRegisters->mOut);
        LOG_INFO("输出时间-秒钟: %d", skDeviceModbusRegisters->sOut);
        LOG_INFO("内部温度: %d", skDeviceModbusRegisters->tempInside);
        LOG_INFO("外部温度: %d", skDeviceModbusRegisters->tempOutside);
        LOG_INFO("按键锁: %d", skDeviceModbusRegisters->keyLock);
        LOG_INFO("保护状态: %d", skDeviceModbusRegisters->protectStatus);
        LOG_INFO("CVCC模式: %d", skDeviceModbusRegisters->cvccMode);
        LOG_INFO("输出使能: %d", skDeviceModbusRegisters->outEnable);
        LOG_INFO("温度单位: %d", skDeviceModbusRegisters->tempUnit);
        LOG_INFO("背光等级: %d", skDeviceModbusRegisters->backlightLevel);
        LOG_INFO("休眠时间: %d", skDeviceModbusRegisters->sleepTime);
        LOG_INFO("设备型号: %d", skDeviceModbusRegisters->skModel);
        LOG_INFO("固件版本号: %d", skDeviceModbusRegisters->skVersion);
        LOG_INFO("ModBus ID: %d", skDeviceModbusRegisters->skModbusId);
        LOG_INFO("ModBus 波特率: %d", skDeviceModbusRegisters->skBaudrate);
        LOG_INFO("内部温度偏移修正: %d", skDeviceModbusRegisters->tempInsideOffset);
        LOG_INFO("外部温度偏移修正: %d", skDeviceModbusRegisters->tempOutsideOffset);
        LOG_INFO("蜂鸣器使能: %d", skDeviceModbusRegisters->buzzerEnable);
        LOG_INFO("快速设置组: %d", skDeviceModbusRegisters->extractCfgGrop);
        LOG_INFO("设备状态: %d", skDeviceModbusRegisters->deviceStatus);
        LOG_INFO("MPPT使能: %d", skDeviceModbusRegisters->mpptEnable);
        LOG_INFO("MPPT最大功率点系数: %d", skDeviceModbusRegisters->mpptK);
        LOG_INFO("电池充电截止电流: %d", skDeviceModbusRegisters->batteryChargeCutoffI);
        LOG_INFO("恒功率使能: %d", skDeviceModbusRegisters->cwEnable);
        LOG_INFO("恒功率值: %d", skDeviceModbusRegisters->cw);
    }
}

/**
 * @brief 初始化前10个寄存器自动读取
 * 
 */
void SKDevice::initTop10RegistersAutoRead() {
    LOG_INFO("SK 初始化常用寄存器定时读取");
    // 创建一个定时器任务，每隔一定时间读取一次前10个寄存器
    xTaskCreate(
        [](void* param) {
            SKDevice* skDevice = static_cast<SKDevice*>(param);
            while (true) {
                // 读取前10个寄存器
                skDevice->readSkDeviceRegisters(); // 读取前10个寄存器
                vTaskDelay(pdMS_TO_TICKS(CONFIG_SK_DEVICE_REGISTERS_READ_INTERVAL)); 
            }
        },
        "SKDeviceAutoReadTask",
        CONFIG_TASK_STACK_SIZE,
        this,
        1,
        nullptr
    ); // 创建任务
    LOG_INFO("SK 常用寄存器定时读取任务创建完成");
}


/**
 * @brief 获取SK设备实例
 * 
 * @return SKDevice* 单实例
 */
SKDevice* SKDevice::getInstance() {
    return instance;
}

/**
 * @brief 获取ModBus寄存器对象
 * 
 * @return SkDeviceModbusRegisters* ModBus寄存器对象
 */
SkDeviceModbusRegisters* SKDevice::getSkDeviceModbusRegisters() {
    return skDeviceModbusRegisters; // 返回ModBus寄存器对象
}

/**
 * @brief 设置SK寄存器
 * 
 * @param register_addr 寄存器地址
 * @param data 寄存器数据
 */
uint16_t SKDevice::setSkDeviceRegister(uint16_t registerAddr, uint16_t data) {
    if (!isWritableRegister(registerAddr)) {
        LOG_ERROR("SK 寄存器地址 %X 不可写", registerAddr);
        return ESP_FAIL;
    }

    //加锁
    xSemaphoreTake(modbusMutex, portMAX_DELAY);
    // 设置寄存器
    skModbus->writeHoldingRegister(CONFIG_SK_DEVICE_MODBUS_ADDRESS, registerAddr, data); 

#ifdef CONFIG_SK_DEVICE_REGISTERS_WRITE_VERIFY_ENABLE
    // 读取寄存器以验证设置是否成功
    uint16_t readData = skModbus->readHoldingRegister(CONFIG_SK_DEVICE_MODBUS_ADDRESS, registerAddr);
    //解锁
    xSemaphoreGive(modbusMutex);
    if (readData != data) {
        LOG_ERROR("SK 寄存器设置失败, 地址: %X, 设置数据: %d, 读取数据: %d", registerAddr, data, readData);
    } else {
        LOG_INFO("SK 寄存器设置成功, 地址: %X, 数据: %d", registerAddr, readData);
    }
    return readData; // 返回读取的数据
#else
    //解锁
    xSemaphoreGive(modbusMutex);
    LOG_INFO("SK 寄存器已设置, 地址: %X, 数据: %d", registerAddr, data);
    return data; // 返回设置的数据
#endif
    
}

bool SKDevice::isWritableRegister(uint16_t registerAddr) {
    return writableRegistersAddress.count(registerAddr);
}


/**
 * @brief 读取SK设备前registerNumber个寄存器 
 * 
 * @param registerNumber 寄存器数量
 * @return uint8_t 错误码，0表示成功
 */
uint8_t SKDevice::readSkDeviceRegisters(uint16_t registerNumber) {
    if (registerNumber > sizeof(SkDeviceModbusRegisters) / sizeof(uint16_t)) {
        LOG_ERROR("SK 读取寄存器数量超过限制");
        return ESP_FAIL; // 返回错误码
    }

    // 采用一次读多个寄存器的方式
    LOG_INFO("SK 读取前 %d 个寄存器", registerNumber);
    //加锁
    xSemaphoreTake(modbusMutex, portMAX_DELAY);
    uint8_t err = skModbus->readHoldingRegister(CONFIG_SK_DEVICE_MODBUS_ADDRESS, 0x0, (uint16_t*)skDeviceModbusRegisters, registerNumber);
    //解锁
    xSemaphoreGive(modbusMutex);
    if (err != 0) {
        LOG_ERROR("SK 读取寄存器失败");
    }
    
    return err;
    // for (size_t i = 0; i < registerNumber; i++) {
    //     uint16_t* p = (uint16_t*)(((size_t)skDeviceModbusRegisters) + i * 2);
    //     //加锁
    //     xSemaphoreTake(modbusMutex, portMAX_DELAY);
    //     *p = skModbus->readHoldingRegister(CONFIG_SK_DEVICE_MODBUS_ADDRESS, i);
    //     //解锁
    //     xSemaphoreGive(modbusMutex);
    // }
}

/**
 * @brief 初始化互斥锁
 * 
 */
void SKDevice::initMutex() {
    // 创建互斥锁
    modbusMutex = xSemaphoreCreateMutex();
    if (modbusMutex == NULL) {
        LOG_ERROR("SK 互斥锁创建失败");
    }
}

/**
 * @brief 读取SK设备寄存器
 * 
 * @param registerAddr 寄存器地址
 * @return uint16_t 寄存器数据
 */
uint16_t SKDevice::readSkDeviceRegister(uint16_t registerAddr) {
    //加锁
    xSemaphoreTake(modbusMutex, portMAX_DELAY);
    uint16_t data = skModbus->readHoldingRegister(CONFIG_SK_DEVICE_MODBUS_ADDRESS, registerAddr); // 读取寄存器
    //解锁
    xSemaphoreGive(modbusMutex);
    return data; // 返回读取的数据
}

