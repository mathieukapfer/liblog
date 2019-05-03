/**
 * @file   log_for_logger.h
 * @author Mathieu <mathieu@debian>
 * @date   Fri May  3 10:02:16 2019
 *
 * @brief  macro to log the logger itself
 *
 *
 */
#ifndef LOG_FOR_LOGGER_H
#define LOG_FOR_LOGGER_H

#include <stdio.h>

#include "log_utils.h"
#include "log_level.h"

// comment this line to kill all log
#define GLOBAL_LOG_ENABLE

// define the max log level
#define GLOBAL_LOG_LEVEL  LP_INFO

// macro to define the local log level
#define ENABLE_LOG(level) static int localLogLevel = LP_##level;

// macro for log
#define LOG_TRACE(fmt, ...)     LOG2(LP_TRACE, "" fmt, ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...)     LOG2(LP_DEBUG, "" fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...)      LOG2(LP_INFO, "" fmt, ##__VA_ARGS__)
#define LOG_NOTICE(fmt, ...)    LOG2(LP_NOTICE, "" fmt, ##__VA_ARGS__)
#define LOG_WARNING(fmt, ...)   LOG2(LP_WARNING, "" fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...)     LOG2(LP_ERROR, "" fmt, ##__VA_ARGS__)
#define LOG_CRITICAL(fmt, ...)  LOG2(LP_CRITICAL, "" fmt, ##__VA_ARGS__)
#define LOG_FATAL(fmt, ...)     LOG2(LP_FATAL, "" fmt, ##__VA_ARGS__)
#define LOG_EMERGENCY(fmt, ...) LOG2(LP_EMERGENCY, "" fmt, ##__VA_ARGS__)

// tge default log is info
#define LOG_(fmt, ...)  LOG_DEBUG(fmt, ##__VA_ARGS__);





// ==================================================================================
// internal engine - do not use this directly
#define LOG2(prio, fmt, ...)		  __LOG__(prio, fmt, ##__VA_ARGS__)

#define min(a, b) (a < b?a:b)

#define _LOG_ISENABLED(priority) (min(localLogLevel, GLOBAL_LOG_LEVEL) >= priority)

// max of "file:line" header
#define LOG_HEADER_SIZE 30

#define LOGGER_LOG_PATH "[LOGGER]"

#ifdef GLOBAL_LOG_ENABLE
#define __LOG__(priority, FMT, ...)                                     \
	if (_LOG_ISENABLED(priority)) {                                       \
    char header[LOG_HEADER_SIZE];                                       \
    snprintf(header, LOG_HEADER_SIZE, "%s:%04d:", basename_const(__FILE__), __LINE__); \
    printf("\n%-25s[%-5s] %-15s %10s():", header, logLevelToString(priority), LOGGER_LOG_PATH, __func__); \
    printf("" FMT, ##__VA_ARGS__);                                      \
    fflush(stdout);                                                     \
  }
#else
#define __LOG__(priority, FMT, ...)
#endif

#endif /* LOG_FOR_LOGGER_H */
