#include <stdarg.h>
#include <stdio.h>
#include "log_event.h"
#include "log_const.h"
#include "log_macro.h"
#include "LogNode.h"

void _log_logEvent(LogNode *logNode, struct LogEvent* ev, ...) {
#if 0
  struct LogCategory* cat = category;
  va_start(ev->ap, ev);
  while (1) {
    struct LogAppender* appender = cat->appender;
    if (appender != NULL) {
      appender->doAppend(appender, ev);
    }
    if (!cat->willLogToParent)
    break;

    cat = cat->parent;
  }
  va_end(ev->ap);
#else
  char logPath[ LOG_CATEGORY_NAME_SIZE_MAX];
  int logLevel = logNode?logNode->_logLevel:0;
  va_start(ev->ap, ev);

  // compute log path
  logNode?logNode->getFullName(logPath,LOG_CATEGORY_NAME_SIZE_MAX):"<out of bound>";
  printf("\n%-20s:%04d:[%-5s][%-22s]%10s():",
         ev->fileName, ev->lineNum, logLevelToString(ev->priority), logPath, ev->functionName);
  printf(ev->fmt, ev->ap);
  va_end(ev->ap);
#endif
} // _log_logEvent
