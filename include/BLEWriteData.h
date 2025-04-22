/**
 * @file BLEWriteData.h
 * @author WorldYun
 * @brief 
 * @version 0.1
 * @date 2025-04-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include <Arduino.h>
#include <BLEDevice.h>
#include "config.h"

class BLEWriteData {

public:
    size_t bleDataLength; // 数据长度
    uint8_t* bleData; // 数据
    uint8_t funCode; // 功能码
    uint8_t* funcData;  // 功能码数据
    size_t funcDataLength;  // 功能码数据长度
    uint16_t registerAddr; // 寄存器地址
    uint16_t registerData; // 寄存器数据


    BLEWriteData(BLECharacteristic* characteristic);
    ~BLEWriteData();
};

