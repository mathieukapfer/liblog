#ifndef LOG_FOR_LOGGER_H
#define LOG_FOR_LOGGER_H

#include <stdio.h>

#include "log_utils.h"
#include "log_level.h"

#define GLOBAL_LOGGER_ENABLE

// macro to log the logger itself
#define ENABLE_LOG(level) static int localLogLevel = LP_##level;

#define _LOG_ISENABLEDV(priority) \
  (localLogLevel >= priority)

#ifdef GLOBAL_LOGGER_ENABLE
#define __LOG__(priority, FMT, ...)                                     \
	if (_LOG_ISENABLEDV(priority)) {                                      \
    printf("\n%s:%04d:[%s]%-20s", basename_const(__FILE__), __LINE__, logLevelToString(localLogLevel), __func__); \
    printf(" " FMT, ##__VA_ARGS__);                                     \
  }
#else
#define __LOG__(priority, FMT, ...)
#endif

/* Macro for log */
#define LOG_TRACE(fmt, ...)     LOG2(LP_TRACE, "" fmt, ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...)     LOG2(LP_DEBUG, "" fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...)      LOG2(LP_INFO, "" fmt, ##__VA_ARGS__)
#define LOG_NOTICE(fmt, ...)    LOG2(LP_NOTICE, "" fmt, ##__VA_ARGS__)
#define LOG_WARNING(fmt, ...)   LOG2(LP_WARNING, "" fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...)     LOG2(LP_ERROR, "" fmt, ##__VA_ARGS__)
#define LOG_CRITICAL(fmt, ...)  LOG2(LP_CRITICAL, "" fmt, ##__VA_ARGS__)
#define LOG_FATAL(fmt, ...)     LOG2(LP_FATAL, "" fmt, ##__VA_ARGS__)
#define LOG_EMERGENCY(fmt, ...) LOG2(LP_EMERGENCY, "" fmt, ##__VA_ARGS__)

#define LOG2(prio, fmt, ...)		  __LOG__(prio, fmt, ##__VA_ARGS__)

// default log is info
#define LOG_(fmt, ...)  LOG_DEBUG(fmt, ##__VA_ARGS__);

#endif /* LOG_FOR_LOGGER_H */
