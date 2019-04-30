#ifndef LOG_MACRO_H
#define LOG_MACRO_H

#include <stdio.h>
#include <stdarg.h>
#include "log_event.h"
#include "log_level.h"
#include "log_utils.h"

//#define DEBUG_LOGGER

// macro to log the logger itself
#ifdef DEBUG_LOGGER
#define LOG_(FMT, ...)                                                   \
  {                                                                     \
    printf("\n%-25s:%04d %-20s", basename_const(__FILE__), __LINE__, __func__); \
    printf(" " FMT, ##__VA_ARGS__);                                     \
  }
#else
#define LOG_(FMT, ...)
#endif

// stuff to create & send the log event
#define _LOG_ISENABLEDV(catv, priority) \
  (catv->_logLevel >= priority)

#ifndef min
#define min(a, b) (a > b ? b : a)
#endif

#ifndef max
#define max(a, b) (a > b ? a : b)
#endif

#define _LOG_(catv, priority, fmt, ...)                                 \
	if (_LOG_ISENABLEDV(catv, priority)) {                                \
		struct LogEvent _log_ev =                                           \
      {catv, priority, __FILE__, __FUNCTION__, __LINE__,  fmt};         \
		_log_logEvent(catv, &_log_ev, ##__VA_ARGS__) ;                 \
	}

#define LOG2(prio, fmt, ...)		  _LOG_(_defaultLogCategory, prio, fmt, ##__VA_ARGS__)

#endif /* LOG_MACRO_H */
