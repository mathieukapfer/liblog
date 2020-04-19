#ifndef LOG_EVENT_H
#define LOG_EVENT_H

#include <stdarg.h>

struct LogEvent {
  void* cat;
  int priority;
  const char* fileName;
  int lineNum;
  int printFunctionName;
  const char* functionName;
  const char *fmt;
  /*va_list ap;*/
};

/// log with header
void _log_logEvent(void *logNode, struct LogEvent *ev, ...);

/// log output api
void _log(const char * format, ...);

#endif /* LOG_EVENT_H */
