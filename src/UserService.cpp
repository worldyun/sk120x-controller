/**
 * @file UserService.cpp
 * @author WorldYun
 * @brief 
 * @version 0.1
 * @date 2025-04-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "UserService.h"
#include "utils/log.h"
#include "SKDevice.h"

UserService* UserService::instance = nullptr;

/**
 * @brief 私有构造函数
 * 
 */
UserService::UserService() { }

/**
 * @brief 获取单例对象
 * 
 * @return UserService* 单例对象
 */
UserService* UserService::getInstance() {
    if (instance == nullptr) {
        instance = new UserService();
    }
    return instance;
} // getInstance

/**
 * @brief 执行功能函数
 * 
 * @param bleWriteData BLE写入数据对象
 */
void UserService::execFunc(BLEWriteData* bleWriteData) {
    LOG_INFO("执行功能函数: 功能码: %d, 数据长度: %d", bleWriteData->funCode, bleWriteData->bleDataLength);
    switch (bleWriteData->funCode) {
        case BLE_FUNC_CODE::SK_READ_ALL_REGISTER:
            LOG_INFO("读取所有寄存器");
            SKDevice::getInstance()->readSkDeviceRegisters();            
            break;
        case BLE_FUNC_CODE::SK_READ_REGISTER:
            LOG_INFO("读取寄存器, 数量: %d", bleWriteData->registerAddr);
            SKDevice::getInstance()->readSkDeviceRegisters(bleWriteData->registerAddr); // 读取寄存器
            break;
        case BLE_FUNC_CODE::SK_WRITE_REGISTER:
            LOG_INFO("写入寄存器: %X, 数据: %d", bleWriteData->registerAddr, bleWriteData->registerData);
            SKDevice::getInstance()->setSkDeviceRegister(bleWriteData->registerAddr, bleWriteData->registerData); // 写入寄存器
            break;
        default:
            LOG_ERROR("未知功能码: %d", bleWriteData->funCode);
            break;
    }
}