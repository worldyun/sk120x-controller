/**
 * @file UserService.h
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
#include "config.h"
#include "utils/log.h"
#include "BLEWriteData.h"

class UserService
{

public:
    static UserService* getInstance(); // 获取单例对象
    void execFunc(BLEWriteData* bleWriteData); // 执行功能函数

private:
    static UserService* instance;
    UserService();

    
};

