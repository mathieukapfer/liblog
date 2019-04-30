#ifndef LOG_MACRO_H
#define LOG_MACRO_H

#include <stdio.h>
#include <stdarg.h>
#include "log_event.h"
#include "log_level.h"

//#define DEBUG_LOGGER

#if 0
#define LOG(FMT, ...)                                                   \
  {                                                                     \
    char catName[ LOG_CATEGORY_NAME_SIZE_MAX];                                                   \
    printf("\n%-20s:%04d:%-10s [%d][%-25s]: ", __FILE__, __LINE__, __func__, \
           defaultLog?defaultLog->_logLevel:0,                          \
           defaultLog?defaultLog->getFullName(catName,LOG_CATEGORY_NAME_SIZE_MAX):"<out of bound>"); \
    printf(" " FMT, ##__VA_ARGS__);                                     \
  }
#endif

#ifdef DEBUG_LOGGER
#define LOG_(FMT, ...)                                                   \
  {                                                                     \
    printf("\n%-25s:%04d %-20s", __FILE__, __LINE__, __func__); \
    printf(" " FMT, ##__VA_ARGS__);                                     \
  }
#else
#define LOG_(FMT, ...)
#endif


#define _LOG_ISENABLEDV(catv, priority) \
  (catv->_logLevel != 0 && catv->_logLevel <= priority)

#ifndef min
#define min(a, b) (a > b ? b : a)
#endif

#ifndef max
#define max(a, b) (a > b ? a : b)
#endif

#define _LOG_(catv, priority, fmt, ...)                                  \
	if (_LOG_ISENABLEDV(catv, priority)) {                                \
		struct LogEvent _log_ev =                                           \
      {catv, min(max(LP_NONE, priority), LP_EMERGENCY),                 \
       __FILE__, __FUNCTION__, __LINE__,  fmt};                         \
		_log_logEvent(catv, &_log_ev, fmt, ##__VA_ARGS__) ;                  \
	}

#define LOG2(prio, fmt, ...)		  _LOG_(_defaultLogCategory, prio, fmt, ##__VA_ARGS__)

#define LOG(fmt, ...) LOG_INFO("" fmt, ##__VA_ARGS__)

#endif /* LOG_MACRO_H */
