#include <stdarg.h>
#include <stdio.h>

//#include <libgen.h>
#include <string.h>

#include "log_utils.h"
#include "log_event.h"
#include "log_const.h"
#include "log_macro.h"
#include "LogNode.h"

#ifndef ENABLE_STDIO
#include "LogFifoI.h"
#include "LogFacade.h"
#endif

/*
   Formater function
   Sample:

   log_test.c:0153:              [NOTIC] [Main]          Hello - in main: !!!!!
   log_test.c:0152:              [DEBUG] [Main]          _DOCTEST_ANON_FUNC_14() ENTER:test ENTER
*/

// uncomment this line to enable stack corruption checker
//#define CHECK_STACK_CORRUPTION

#ifdef CHECK_STACK_CORRUPTION
static const char GUARD_VALUE[]="END!";
#endif

#define REMAINING_BUFFER_SIZE(pos) (((LOG_MESSAGE_SIZE_MAX - pos) > 0)?(LOG_MESSAGE_SIZE_MAX - pos):0)
#define SNPRINTF_APPEND(pos, fmt, ...) pos += snprintf(logMessage + pos, REMAINING_BUFFER_SIZE(pos), fmt, ##__VA_ARGS__);
#define VSNPRINTF_APPEND(pos, fmt, ap) pos += vsnprintf(logMessage + pos, REMAINING_BUFFER_SIZE(pos), fmt, ap);

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
  int pos=0;
  va_list ap;
  // unique formateur for all nodes
  char logPath[LOG_CATEGORY_NAME_SIZE_MAX];
  // int logLevel = logNode?logNode->_logLevel:0;
  char header[LOG_HEADER_SIZE];

#ifdef CHECK_STACK_CORRUPTION
  char logMessage[LOG_MESSAGE_SIZE_MAX + sizeof(GUARD_VALUE)];
  strncpy(&logMessage[LOG_MESSAGE_SIZE_MAX], GUARD_VALUE, sizeof(GUARD_VALUE));
#else
  char logMessage[LOG_MESSAGE_SIZE_MAX];
#endif

  va_start(ap, ev);

  // compute log tag path
  logPath[0] = '[';
  logNode?logNode->getFullName(&logPath[1],LOG_CATEGORY_NAME_SIZE_MAX-1):"<unknown>";
  snprintf(header, LOG_HEADER_SIZE, "%s:%04d:", basename_const(ev->fileName), ev->lineNum);

  // compute log header
  SNPRINTF_APPEND(pos, "\n%-30s[%-5s] %-15s ", header, logLevelToString(ev->priority),
                  strncat(logPath,"]", LOG_CATEGORY_NAME_SIZE_MAX));
  if (ev->printFunctionName) {
     SNPRINTF_APPEND(pos, "%10s() ", ev->functionName);
  }
  // compute log body
  VSNPRINTF_APPEND(pos, ev->fmt, ap);

#ifdef ENABLE_STDIO
  // use stdout
  fflush(stdout);
  printf("%s", logMessage);
#else
  // use fifo
  LogFifoI *fifo = LogFacade::inst().getFifo();
  if( fifo && (fifo->isFull() == false) ) {
    fifo->push(logMessage);
  }
#endif

  // end of variadic
  va_end(ap);

#ifdef CHECK_STACK_CORRUPTION
  // check stack corruption
  if (memcmp(&logMessage[LOG_MESSAGE_SIZE_MAX], GUARD_VALUE, sizeof(GUARD_VALUE) != 0)) {
    // Go into an infinite loop to catch the memory corruption on debugger
      while(1)
    {
    }
  }
#endif

#endif

} // _log_logEvent
