/**
 * @file log.h
 * @author WorldYun
 * @brief 
 * @version 0.1
 * @date 2025-04-21
 * @note 此头文件定义了日志记录的宏和函数，用于在代码中输出不同级别的日志信息。
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <ArduinoLog.h>

#ifndef LOG_H
#define LOG_H

// 条件日志宏定义
#if CONFIG_LOG_LEVEL >= LOG_LEVEL_INFO
#define LOG_INFO(msg, ...)   Log.infoln("[%s:%s:%d] " msg, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define LOG_INFO(msg, ...)
#endif

#if CONFIG_LOG_LEVEL >= LOG_LEVEL_ERROR
#define LOG_ERROR(msg, ...)  Log.errorln("[%s:%s:%d] " msg, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define LOG_ERROR(msg, ...)
#endif

#if CONFIG_LOG_LEVEL >= LOG_LEVEL_WARNING
#define LOG_WARNING(msg, ...) Log.warningln("[%s:%s:%d] " msg, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define LOG_WARNING(msg, ...)
#endif

#if CONFIG_LOG_LEVEL >= LOG_LEVEL_NOTICE
#define LOG_NOTICE(msg, ...) Log.noticeln("[%s:%s:%d] " msg, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define LOG_NOTICE(msg, ...)
#endif

#if CONFIG_LOG_LEVEL >= LOG_LEVEL_FATAL
#define LOG_FATAL(msg, ...)  Log.fatal("[%s:%s:%d] " msg, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define LOG_FATAL(msg, ...)
#endif

#if CONFIG_LOG_LEVEL >= LOG_LEVEL_TRACE
#define LOG_TRACE(msg, ...)  Log.traceln("[%s:%s:%d] " msg, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define LOG_TRACE(msg, ...)
#endif

#if CONFIG_LOG_LEVEL >= LOG_LEVEL_VERBOSE
#define LOG_VERBOSE(msg, ...) Log.verbose("[%s:%s:%d] " msg, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define LOG_VERBOSE(msg, ...)
#endif

#endif