#include <Arduino.h>
#include "utils/log.h"
#include "config.h"

void printTimestamp(Print *_logOutput)
{

    // Division constants
    const unsigned long MSECS_PER_SEC = 1000;
    const unsigned long SECS_PER_MIN = 60;
    const unsigned long SECS_PER_HOUR = 3600;
    const unsigned long SECS_PER_DAY = 86400;

    // Total time
    const unsigned long msecs = millis();
    const unsigned long secs = msecs / MSECS_PER_SEC;

    // Time in components
    const unsigned long MiliSeconds = msecs % MSECS_PER_SEC;
    const unsigned long Seconds = secs % SECS_PER_MIN;
    const unsigned long Minutes = (secs / SECS_PER_MIN) % SECS_PER_MIN;
    const unsigned long Hours = (secs % SECS_PER_DAY) / SECS_PER_HOUR;

    // Time as string
    char timestamp[20];
    sprintf(timestamp, "%02d:%02d:%02d.%03d ", Hours, Minutes, Seconds, MiliSeconds);
    _logOutput->print(timestamp);
}

void printLogLevel(Print *_logOutput, int logLevel)
{
    /// Show log description based on log level
    switch (logLevel)
    {
    default:
    case 0:
        _logOutput->print("SILENT ");
        break;
    case 1:
        _logOutput->print("FATAL ");
        break;
    case 2:
        _logOutput->print("ERROR ");
        break;
    case 3:
        _logOutput->print("WARNING ");
        break;
    case 4:
        _logOutput->print("INFO ");
        break;
    case 5:
        _logOutput->print("TRACE ");
        break;
    case 6:
        _logOutput->print("VERBOSE ");
        break;
    }
}

void printSuffix(Print *_logOutput, int logLevel)
{
    _logOutput->print("");
}

void printPrefix(Print *_logOutput, int logLevel)
{
    printTimestamp(_logOutput);
    printLogLevel(_logOutput, logLevel);
}

void logInit()
{
    // 初始化日志
    while (!Serial && !Serial.available()){}
    Log.setPrefix(printPrefix); // set prefix similar to NLog
    Log.setSuffix(printSuffix); // set suffix 
    Log.begin(CONFIG_LOG_LEVEL, &Serial);
    Log.setShowLevel(false);    // Do not show loglevel, we will do this in the prefix
    LOG_INFO("Log 日志初始化完成");
}
