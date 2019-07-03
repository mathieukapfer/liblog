#include <stdarg.h>
#include <stdio.h>

#ifndef ENABLE_STDIO
#define GLOBALLOGMESSAGE_SIZE 10
char globalLogMessage[GLOBALLOGMESSAGE_SIZE];
#endif

//#include <libgen.h>
#include <string.h>

#include "log_utils.h"
#include "log_event.h"
#include "log_const.h"
#include "log_macro.h"
#include "LogNode.h"

/*
   Formater function
   Sample:

   log_test.c:0153:              [NOTIC] [Main]          Hello - in main: !!!!!
   log_test.c:0152:              [DEBUG] [Main]          _DOCTEST_ANON_FUNC_14() ENTER:test ENTER
*/
void _log_logEvent(LogNode *logNode, struct LogEvent* ev, ...) {
#if 0
  // TODO: add capability to define a formater per node
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
  // unique formateur for all nodes
  char logPath[LOG_CATEGORY_NAME_SIZE_MAX];
  int logLevel = logNode?logNode->_logLevel:0;
  char header[LOG_HEADER_SIZE];
  char logMessage[LOG_MESSAGE_SIZE_MAX];
  int pos=0;

  va_start(ev->ap, ev);

  // compute log path
  logPath[0] = '[';
  logNode?logNode->getFullName(&logPath[1],LOG_CATEGORY_NAME_SIZE_MAX-1):"<out of bound>";
  snprintf(header, LOG_HEADER_SIZE, "%s:%04d:", basename_const(ev->fileName), ev->lineNum);
  pos +=snprintf(logMessage, LOG_MESSAGE_SIZE_MAX, "\n%-30s[%-5s] %-15s ",
           header, logLevelToString(ev->priority), strncat(logPath,"]", LOG_CATEGORY_NAME_SIZE_MAX));
  if (ev->printFunctionName) {
    pos +=snprintf(logMessage, LOG_MESSAGE_SIZE_MAX, "%10s() ", ev->functionName);
  }
  vsnprintf(logMessage, LOG_MESSAGE_SIZE_MAX, ev->fmt, ev->ap);

#ifdef ENABLE_STDIO
  fflush(stdout);
  printf("%s", logMessage);
#else
  strncpy(globalLogMessage, logMessage, GLOBALLOGMESSAGE_SIZE);
#endif

  // end of variadic
  va_end(ev->ap);
#endif
} // _log_logEvent
