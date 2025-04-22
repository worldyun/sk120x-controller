/**
 * @file sk_device_registers.h
 * @author WorldYun
 * @brief 
 * @version 0.1
 * @date 2025-04-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __SK120X_CTRL_SK_DEVICE_REGISTERS_H__
#define __SK120X_CTRL_SK_DEVICE_REGISTERS_H__

#include <Arduino.h>

struct SkDeviceModbusRegisters {
    uint16_t vSet;                // 设置电压
    uint16_t iSet;                // 设置电流
    uint16_t vOut;                // 输出电压
    uint16_t iOut;                // 输出电流
    uint16_t wOut;                // 输出功率
    uint16_t vIn;                 // 输入电压
    uint32_t ahOut;               // 输出安时 (低2字节: ahOutLow, 高2字节: ahOutHigh)
    uint32_t whOut;               // 输出瓦时 (低2字节: whOutLow, 高2字节: whOutHigh)
    uint16_t hOut;                // 输出时间-小时
    uint16_t mOut;                // 输出时间-分钟
    uint16_t sOut;                // 输出时间-秒钟
    uint16_t tempInside;          // 内部温度
    uint16_t tempOutside;         // 外部温度
    uint16_t keyLock;             // 按键锁
    uint16_t protectStatus;       // 保护状态
    uint16_t cvccMode;            // CVCC模式
    uint16_t outEnable;           // 输出使能
    uint16_t tempUnit;            // 温度单位
    uint16_t backlightLevel;      // 背光等级
    uint16_t sleepTime;           // 休眠时间
    uint16_t skModel;             // 设备型号
    uint16_t skVersion;           // 固件版本号
    uint16_t skModbusId;          // ModBus ID
    uint16_t skBaudrate;          // ModBus 波特率
    uint16_t tempInsideOffset;    // 内部温度偏移修正
    uint16_t tempOutsideOffset;   // 外部温度偏移修正
    uint16_t buzzerEnable;        // 蜂鸣器使能
    uint16_t extractCfgGrop;      // 快速设置组
    uint16_t deviceStatus;        // 设备状态
    uint16_t mpptEnable;          // MPPT使能
    uint16_t mpptK;               // MPPT最大功率点系数
    uint16_t batteryChargeCutoffI;// 电池充电截止电流
    uint16_t cwEnable;            // 恒功率使能
    uint16_t cw;                  // 恒功率值
};

struct SkDeviceModbusCfgGroupRegisters {
    uint16_t vSet;                  // 设置电压
    uint16_t iSet;                  // 设置电流
    uint16_t protectLowVoltage;     // 低电压保护值
    uint16_t protectOverVoltage;    // 过压保护值
    uint16_t protectOverCurrent;    // 过流保护值
    uint16_t protectOverPower;      // 过功率保护值
    uint16_t hMaxOut;               // 最大输出时间-小时
    uint16_t mMaxOut;               // 最大输出时间-分钟
    uint32_t ahMaxOut;              // 最大输出安时 (低2字节: ahMaxOutLow, 高2字节: ahMaxOutHigh)
    uint32_t whMaxOut;              // 最大输出瓦时 (低2字节: whMaxOutLow, 高2字节: whMaxOutHigh)
    uint16_t protectOverTempInside; // 内部过温保护值
    uint16_t powerOnOutEnable;      // 上电输出使能
    uint16_t protectOverTempOutside;// 外部过温保护值
};

#endif // __SK120X_CTRL_SK_DEVICE_REGISTERS_H__