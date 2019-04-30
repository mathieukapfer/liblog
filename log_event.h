#ifndef LOG_EVENT_H
#define LOG_EVENT_H

#include <stdarg.h>

// foward declaration
class LogNode;

struct LogEvent {
  LogNode* cat;
  int priority;
  const char* fileName;
  const char* functionName;
  int lineNum;
  const char *fmt;
  va_list ap;
};

void _log_logEvent(LogNode *logNode, struct LogEvent *ev, ...);

#endif /* LOG_EVENT_H */
