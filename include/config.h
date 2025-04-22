/**
 * @file config.h
 * @author WorldYun
 * @brief 
 * @version 0.1
 * @date 2025-04-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __SK120X_CTRL_CONFIG_H__
#define __SK120X_CTRL_CONFIG_H__

    //设备名称
    #define CONFIG_DEVICE_NAME "SK120X"

    //设备软件版本号
    #define CONFIG_DEVICE_VERSION "0.0.1"

    //设备硬件版本号
    #define CONFIG_DEVICE_HARDWARE_VERSION "0.0.1"

    //日志级别
    #define CONFIG_LOG_LEVEL LOG_LEVEL_INFO

    //BLE功率
    #define CONFIG_BLE_POWER_LVL ESP_PWR_LVL_P9

    //BLE MTU大小
    #define CONFIG_BLE_MTU 512

    //BLE服务UUID
    #define CONFIG_BLE_SERVICE_UUID "1bb2b7e6-6769-4346-b8c3-413c97b29185"

    //BLE服务Get All Config Characteristic UUID
    #define CONFIG_BLE_GET_ALL_CONFIG_CHARACTERISTIC_UUID "c2d4ff46-5424-4b37-b3a4-e4a2ee4a4b0a"

    //BLE服务Set Config Characteristic UUID
    #define CONFIG_BLE_SET_CONFIG_CHARACTERISTIC_UUID "5f734ee8-4ff7-4fde-8918-61a363974e6e"

#endif