/**
 * @file main.cpp
 * @author WorldYun
 * @brief 
 * @version 0.1
 * @date 2025-04-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <Arduino.h>
#include "log_init.h"
#include "utils/log.h"
#include "config.h"
#include "BLE.h"
#include "SKDevice.h"

void setup() {
    Serial.begin(115200);
    Serial.println("Setup Start!");

    // 初始化日志
    logInit();
    // 初始化 BLE 服务
    BLE::init();

    // 等待2秒以确保SK设备启动完成
    LOG_INFO("等待 SK 设备启动");
    vTaskDelay(pdMS_TO_TICKS(CONFIG_SK_DEVICE_STARTUP_WAIT_TIME));

    // 初始化 SK 设备
    SKDevice::init();

    LOG_INFO("Setup done!");
}

void loop() {
    // 永久挂起当前任务, 以节省 CPU 资源
    vTaskSuspend(NULL);
}