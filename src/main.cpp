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

void setup() {
    Serial.begin(115200);
    Serial.println("Setup Start!");

    // 初始化日志
    logInit();
    // 初始化 BLE 服务
    BLE::init();

    LOG_INFO("Setup done!");
}

void loop() {
    delay(1000);
}