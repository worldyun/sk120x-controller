/**
 * @file SKDevice.h
 * @author WorldYun
 * @brief 
 * @version 0.1
 * @date 2025-04-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#pragma once

#include "config.h"
#include <Arduino.h>
#include <DFRobot_RTU.h>
#include "sk_device_registers.h"
#include <set>



class SKDevice
{
public:
    bool isInited = false; // 是否初始化完成
    static void init();
    static SKDevice* getInstance();
    SkDeviceModbusRegisters* getSkDeviceModbusRegisters(); // 获取ModBus寄存器对象
    uint16_t setSkDeviceRegister(uint16_t registerAddr, uint16_t data); // 设置SK寄存器
    uint8_t readSkDeviceRegisters(uint16_t registerNumber = sizeof(SkDeviceModbusRegisters) / sizeof(uint16_t));   // 读取SK设备前registerNumber个寄存器 
    uint16_t readSkDeviceRegister(uint16_t registerAddr); // 读取SK设备寄存器


private:
    static SKDevice* instance;
    DFRobot_RTU * skModbus; // ModBus RTU对象
    SkDeviceModbusRegisters* skDeviceModbusRegisters; // ModBus寄存器对象
    const std::set<uint16_t> writableRegistersAddress = {CONFIG_SK_DEVICE_WRITABLE_REGISTERS_ADDRESS}; // 可写寄存器地址集合
    bool isWritableRegister(uint16_t registerAddr); // 判断寄存器是否可写
    SemaphoreHandle_t modbusMutex; // 互斥锁


    SKDevice();
    ~SKDevice();
    void initSKSerialAndModbus();   // 初始化SK串口与ModBus
    void initSKDeviceRegisters(); // 初始化SK设备寄存器
    void initTop10RegistersAutoRead(); // 初始化前10个寄存器自动读取
    void initMutex(); // 初始化互斥锁

};
