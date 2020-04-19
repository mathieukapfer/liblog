#ifndef LOG_MACRO_H
#define LOG_MACRO_H

//#include <stdio.h>
#include <stdarg.h>
#include "log_event.h"
#include "log_level.h"
#include "log_utils.h"

#ifdef __cplusplus
// add fonction template
#include "log_formater.h"
#endif

#include "log_facade.h"


// stuff to create & send the log event
#define _LOG_ISENABLED(catv, priority) \
  (getLogLevel((void *)catv) >= priority)

#define _LOG_(catv, priority, fct, fmt, ...)                            \
  if (_LOG_ISENABLED((void *)catv, priority)) {                         \
    struct LogEvent _log_ev =						\
      {(void *)catv, priority, __FILE__, __LINE__, fct, __FUNCTION__, fmt}; \
    _log_logEvent( (void *) catv, &_log_ev, ##__VA_ARGS__) ;        \
  }

#define LOG2(prio, fct, fmt, ...)		  \
  {                                                                     \
    /* buffer for log formater function - see log_formater.h */         \
    const int logBufSize = 255;                                         \
    char logBuf[logBufSize];                                            \
    (void) logBuf;                                                      \
    _LOG_(_defaultLogCategory, prio, fct, fmt, ##__VA_ARGS__)           \
  }

#endif /* LOG_MACRO_H */
