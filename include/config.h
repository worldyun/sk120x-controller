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

    //BLE服务Notify Top10 Reg Characteristic UUID
    #define CONFIG_BLE_NOTIFY_TOP10_REG_CHARACTERISTIC_UUID "f2c4b5a0-1d3e-4b8f-9c6d-7a2e5f3b8a0b"

    //BLE服务Notify Top10 Reg 通知间隔时间 200ms
    #define CONFIG_BLE_NOTIFY_TOP10_REG_INTERVAL 200

    //BLE服务Notify Top10 Reg 字节数
    #define CONFIG_BLE_NOTIFY_TOP10_REG_SIZE 20

    //SK设备串口RX引脚
    #define CONFIG_SK_DEVICE_SERIAL_RX_PIN GPIO_NUM_18

    //SK设备串口TX引脚
    #define CONFIG_SK_DEVICE_SERIAL_TX_PIN GPIO_NUM_19

    //SK设备串口波特率
    #define CONFIG_SK_DEVICE_SERIAL_BAUD_RATE 115200

    //ModBus广播地址
    #define CONFIG_MODBUS_BROADCAST_ADDRESS 0x00

    //SK设备ModBus地址
    #define CONFIG_SK_DEVICE_MODBUS_ADDRESS 0x01

    //SK设备AllConfig大小   24*2=48字节
    #define CONFIG_SK_DEVICE_ALL_CONFIG_SIZE 36*2

    //SK 常用寄存器地址定时读取间隔时间 200ms
    #define CONFIG_SK_DEVICE_REGISTERS_READ_INTERVAL 200

    //SK设备可写寄存器地址
    #define CONFIG_SK_DEVICE_WRITABLE_REGISTERS_ADDRESS SK_DEVICE_MODBUS_REGISTER_ADDRESS::V_SET, \
                                                        SK_DEVICE_MODBUS_REGISTER_ADDRESS::I_SET, \
                                                        SK_DEVICE_MODBUS_REGISTER_ADDRESS::KEY_LOCK, \
                                                        SK_DEVICE_MODBUS_REGISTER_ADDRESS::OUT_ENABLE, \
                                                        SK_DEVICE_MODBUS_REGISTER_ADDRESS::TEMP_UNIT, \
                                                        SK_DEVICE_MODBUS_REGISTER_ADDRESS::BACKLIGHT_LEVEL, \
                                                        SK_DEVICE_MODBUS_REGISTER_ADDRESS::SLEEP_TIME, \
                                                        SK_DEVICE_MODBUS_REGISTER_ADDRESS::TEMP_INSIDE_OFFSET, \
                                                        SK_DEVICE_MODBUS_REGISTER_ADDRESS::TEMP_OUTSIDE_OFFSET, \
                                                        SK_DEVICE_MODBUS_REGISTER_ADDRESS::BUZZER_ENABLE, \
                                                        SK_DEVICE_MODBUS_REGISTER_ADDRESS::EXTRACT_CFG_GROP, \

    //寄存器写入后再次读取以验证是否成功 启用表示
    //如果不需要验证可以注释掉
    #define CONFIG_SK_DEVICE_REGISTERS_WRITE_VERIFY_ENABLE

    //操作码枚举
    namespace BLE_FUNC_CODE {
        enum BLE_FUNC_CODE_ENUM {
            SK_READ_REGISTER = 0x00,     //读寄存器
            SK_WRITE_REGISTER = 0x01,    //写寄存器
            SK_READ_ALL_REGISTER = 0x03, //读所有寄存器
        };
    };

    //SK设备ModBus寄存器地址
    namespace SK_DEVICE_MODBUS_REGISTER_ADDRESS {
        enum SK_DEVICE_MODBUS_REGISTER_ADDRESS_ENUM {
            V_SET = 0x0000,     //设置电压
            I_SET = 0x0001,     //设置电流
            V_OUT = 0x0002,     //输出电压
            I_OUT = 0x0003,     //输出电流
            W_OUT = 0x0004, //输出功率
            V_IN = 0x0005,      //输入电压
            AH_OUT_LOW = 0x0006,    //输出安时低2字节
            AH_OUT_HIGH = 0x0007,   //输出安时高2字节
            WH_OUT_LOW = 0x0008,    //输出瓦时低2字节
            WH_OUT_HIGH = 0x0009,   //输出瓦时高2字节
            H_OUT = 0x000A,     //输出时间-小时
            M_OUT = 0x000B,     //输出时间-分钟
            S_OUT = 0x000C,     //输出时间-秒钟
            TEMP_INSIDE = 0x000D,  //内部温度
            TEMP_OUTSIDE = 0x000E, //外部温度
            KEY_LOCK = 0x000F,  //按键锁
            PROTECT_STATUS = 0x0010, //保护状态
            CVCC_MODE = 0x0011, //CVCC模式
            OUT_ENABLE = 0x0012, //输出使能
            TEMP_UNIT = 0x0013, //温度单位
            BACKLIGHT_LEVEL = 0x0014, //背光等级
            SLEEP_TIME = 0x0015, //休眠时间
            SK_MODEL = 0x0016, //设备型号
            SK_VERSION = 0x0017, //固件版本号
            SK_MODBUS_ID = 0x0018, //ModBus ID
            SK_BAUDRATE = 0x0019, //ModBus 波特率
            TEMP_INSIDE_OFFSET = 0x001A, //内部温度偏移修正
            TEMP_OUTSIDE_OFFSET = 0x001B, //外部温度偏移修正
            BUZZER_ENABLE = 0x001C, //蜂鸣器使能
            EXTRACT_CFG_GROP = 0x001D, //快速设置组
            DEVICE_STATUS = 0x001E, //设备状态
            MPPT_ENABLE = 0x001F, //MPPT使能
            MPPT_K = 0x0020, //MPPT最大功率点系数
            BATTERY_CHARGE_CUTOFF_I = 0x0021,   //电池充电截止电流
            CW_ENABLE = 0x0022, //恒功率使能
            CW = 0x0023, //恒功率值
        };
    }


    //SK设备ModBus设置组寄存器地址
    namespace SK_DEVICE_MODBUS_CFG_GROUP_REGISTER_ADDRESS {
        enum SK_DEVICE_MODBUS_CFG_GROUP_REGISTER_ADDRESS_ENUM {
            V_SET = 0x00,   //设置电压
            I_SET = 0x01,   //设置电流
            PROTECT_LOW_VOLTAGE = 0x02, //低电压保护值
            PROTECT_OVER_VOLTAGE = 0x03, //过压保护值
            PROTECT_OVER_CURRENT = 0x04, //过流保护值
            PROTECT_OVER_POWER = 0x05, //过功率保护值
            H_MAX_OUT = 0x06, //最大输出时间-小时
            M_MAX_OUT = 0x07, //最大输出时间-分钟
            AH_MAX_OUT_LOW = 0x08, //最大输出安时低2字节
            AH_MAX_OUT_HIGH = 0x09, //最大输出安时高2字节
            WH_MAX_OUT_LOW = 0x0A, //最大输出瓦时低2字节
            WH_MAX_OUT_HIGH = 0x0B, //最大输出瓦时高2字节
            PROTECT_OVER_TEMP_INSIDE = 0x0C, //内部过温保护值
            POWER_ON_OUT_ENABLE = 0x0D, //上电输出使能
            PROTECT_OVER_TEMP_OUTSIDE = 0x0E, //外部过温保护值
        };
    }

#endif