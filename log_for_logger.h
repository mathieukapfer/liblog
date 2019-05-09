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

#include "log_const.h"
#include "log_utils.h"
#include "log_level.h"
#include "log.h"

// remove macro that should not be used to log the logger
#undef LOG_REGISTER
#undef LOG_CONFIGURE
#undef LOG_DISLAY_TREE

// define the local log level statically
#define ENABLE_LOG(level) static int localLogLevel = LP_##level;

// Log level control
// ======================
// comment this line to kill all log
#define GLOBAL_LOG_ENABLE

// define the max log level
#define GLOBAL_LOG_LEVEL  LP_INFO

// macro for log => see log.h

// optinally display function name
//#define DISPLAY_FCT_NAME

// ==================================================================================
// internal engine - do not use this directly
#undef LOG2
#define LOG2(prio, fmt, ...)		  __LOG__(prio, fmt, ##__VA_ARGS__)

#define min(a, b) (a < b?a:b)

#undef _LOG_ISENABLED
#define _LOG_ISENABLED(priority) (min(localLogLevel, GLOBAL_LOG_LEVEL) >= priority)

#define LOGGER_LOG_PATH "[LOGGER]"

#ifdef GLOBAL_LOG_ENABLE
#define __LOG__(priority, FMT, ...)                                     \
	if (_LOG_ISENABLED(priority)) {                                       \
    char header[LOG_HEADER_SIZE];                                       \
    snprintf(header, LOG_HEADER_SIZE, "%s:%04d:", basename_const(__FILE__), __LINE__); \
    printf("\n%-45s[%-5s] %-15s", header, logLevelToString(priority), LOGGER_LOG_PATH); \
    printf("" FMT, ##__VA_ARGS__);                                      \
    fflush(stdout);                                                     \
  }
#else
#define __LOG__(priority, FMT, ...)
#endif

#ifdef DISPLAY_FCT_NAME
  printf("%10s():", __FUNCTION__);
#endif


#endif /* LOG_FOR_LOGGER_H */
