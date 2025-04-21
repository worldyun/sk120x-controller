#include <ArduinoLog.h>

#ifndef LOG_H
#define LOG_H
#define LOG_INFO(msg, ...)   Log.infoln("[%s:%s:%d] " msg, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOG_ERROR(msg, ...)  Log.errorln("[%s:%s:%d] " msg, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOG_WARNING(msg, ...) Log.warningln("[%s:%s:%d] " msg, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOG_NOTICE(msg, ...) Log.noticeln("[%s:%s:%d] " msg, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOG_FATAL(msg, ...)  Log.fatal("[%s:%s:%d] " msg, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOG_TRACE(msg, ...)  Log.traceln("[%s:%s:%d] " msg, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOG_VERBOSE(msg, ...) Log.verbose("[%s:%s:%d] " msg, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#endif