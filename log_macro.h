#ifndef LOG_MACRO_H
#define LOG_MACRO_H

#include <stdio.h>
#include <stdarg.h>
#include "log_event.h"
#include "log_level.h"
#include "log_utils.h"

// stuff to create & send the log event
#define _LOG_ISENABLED(catv, priority) \
  (catv->_logLevel >= priority)

#define _LOG_(catv, priority, fmt, ...)                                 \
	if (_LOG_ISENABLED(catv, priority)) {                                \
		struct LogEvent _log_ev =                                           \
      {catv, priority, __FILE__, __FUNCTION__, __LINE__,  fmt};         \
		_log_logEvent(catv, &_log_ev, ##__VA_ARGS__) ;                 \
	}

#define LOG2(prio, fmt, ...)		  _LOG_(_defaultLogCategory, prio, fmt, ##__VA_ARGS__)

#endif /* LOG_MACRO_H */
