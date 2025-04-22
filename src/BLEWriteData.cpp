/**
 * @file BLEWriteData.cpp
 * @author WorldYun
 * @brief 
 * @version 0.1
 * @date 2025-04-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "BLEWriteData.h"

BLEWriteData::BLEWriteData(BLECharacteristic* characteristic) {
    bleDataLength = characteristic->getLength(); // 获取数据长度
    bleData = (uint8_t *)malloc(bleDataLength); // 分配内存
    //复制数据到bleData
    memcpy(bleData, characteristic->getData(), bleDataLength);
    funCode = bleData[0]; // 获取功能码
    funcData = (uint8_t*)((size_t)bleData + 1); // 获取功能码数据
    funcDataLength = bleDataLength - 1; // 获取功能码数据长度
    if (funCode == BLE_FUNC_CODE::SK_READ_REGISTER || funCode == BLE_FUNC_CODE::SK_WRITE_REGISTER) {
        registerAddr = *(uint16_t*)((size_t)bleData + 1); // 获取寄存器地址
    }
    if (funCode == BLE_FUNC_CODE::SK_WRITE_REGISTER) {
        registerData = *(uint16_t*)((size_t)bleData + 3); // 获取寄存器数据
    }
}

BLEWriteData::~BLEWriteData() {
    free(bleData);
}