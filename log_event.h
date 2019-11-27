#ifndef LOG_EVENT_H
#define LOG_EVENT_H

#include <stdarg.h>

// forward declaration
class LogNode;

struct LogEvent {
  LogNode* cat;
  int priority;
  const char* fileName;
  int lineNum;
  bool printFunctionName;
  const char* functionName;
  const char *fmt;
  /*va_list ap;*/
};

/// log with header
void _log_logEvent(LogNode *logNode, struct LogEvent *ev, ...);

/// log output api
void _log(const char * format, ...);

#endif /* LOG_EVENT_H */
