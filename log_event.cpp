#include <stdarg.h>
#include <stdio.h>
#include <libgen.h>
#include <string.h>

#include "log_utils.h"
#include "log_event.h"
#include "log_const.h"
#include "log_macro.h"
#include "LogNode.h"


// formater function
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
  char logPath[LOG_CATEGORY_NAME_SIZE_MAX];
  int logLevel = logNode?logNode->_logLevel:0;
  char header[LOG_HEADER_SIZE];

  va_start(ev->ap, ev);

  // compute log path
  logPath[0] = '[';
  logNode?logNode->getFullName(&logPath[1],LOG_CATEGORY_NAME_SIZE_MAX-1):"<out of bound>";
  snprintf(header, LOG_HEADER_SIZE, "%s:%04d:", basename_const(ev->fileName), ev->lineNum);
  printf("\n%-25s[%-5s] %-15s %10s():",
         header, logLevelToString(ev->priority), strncat(logPath,"]",LOG_CATEGORY_NAME_SIZE_MAX), \
         ev->functionName);
  vprintf(ev->fmt, ev->ap);
  fflush(stdout);
  va_end(ev->ap);
#endif
} // _log_logEvent
