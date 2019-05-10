#ifndef LOG_EVENT_H
#define LOG_EVENT_H

#include <stdarg.h>

// foward declaration
class LogNode;

struct LogEvent {
  LogNode* cat;
  int priority;
  const char* fileName;
  int lineNum;
  bool printFunctionName;
  const char* functionName;
  const char *fmt;
  va_list ap;
};

void _log_logEvent(LogNode *logNode, struct LogEvent *ev, ...);

#endif /* LOG_EVENT_H */
