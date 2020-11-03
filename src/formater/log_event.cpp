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

#ifdef ENABLE_SYS_LOG
#include "log_event_syslog.h"
#endif

#include "log_timestamp.h"

#define TIMESTAMP_SIZE 10

/*
   Formater function
   Sample:

 0000.7289 AuthentConfig.cpp:0022:       [<NOTIC>] [AuthentConfig] registerModbusIndex() ENTER:
 0000.7290 MaintenanceDb.cpp:0025:       [<NOTIC>] [MaintenanceDb] registerModbusIndex() ENTER:
 0000.7291 AuthentDb.cpp:0054:           [<NOTIC>] [authen.Db]     registerModbusIndex() ENTER:
 0000.7292 IoCpwIpc.cpp:0040:            [<NOTIC>] [iocpw.ipc]     registerSharedIndex() ENTER:
 0000.7293 IoCpwIpc.cpp:0059:            [<NOTIC>] [iocpw.ipc]     registerModbusIndex() ENTER:

*/

// uncomment this line to enable stack corruption checker
//#define CHECK_STACK_CORRUPTION

#ifdef CHECK_STACK_CORRUPTION
static const char GUARD_VALUE[]="END!";
#endif

#define REMAINING_BUFFER_SIZE(pos) (((LOG_MESSAGE_SIZE_MAX - pos) > 0)?(LOG_MESSAGE_SIZE_MAX - pos):0)
#define SNPRINTF_APPEND(pos, fmt, ...) pos += snprintf(logMessage + pos, REMAINING_BUFFER_SIZE(pos), fmt, ##__VA_ARGS__);
#define VSNPRINTF_APPEND(pos, fmt, ap) pos += vsnprintf(logMessage + pos, REMAINING_BUFFER_SIZE(pos), fmt, ap);

void _log_logEvent(void *_log_node, struct LogEvent* ev, ...) {
  int pos=0;
  va_list ap;
  // unique formateur for all nodes
  char logPath[LOG_CATEGORY_PATH_NAME_SIZE_MAX];
  char *logPathPtr = logPath;
  // int logLevel = logNode?logNode->_logLevel:0;
  char file_line[LOG_FILE_LINE_SIZE];

#ifdef CHECK_STACK_CORRUPTION
  char logMessage[LOG_MESSAGE_SIZE_MAX + sizeof(GUARD_VALUE)];
  strncpy(&logMessage[LOG_MESSAGE_SIZE_MAX], GUARD_VALUE, sizeof(GUARD_VALUE));
#else
  char logMessage[LOG_MESSAGE_SIZE_MAX];
#endif


  LogNode *logNode = (LogNode *)_log_node;

  va_start(ap, ev);

  // compute log path once
  if (logNode->_isPathInitialized) {
    // switch pointer
    logPathPtr = logNode->_path;
  } else {
    // compute it
    logPath[0] = '[';
    logNode?logNode->getFullName(&logPath[1],LOG_CATEGORY_PATH_NAME_SIZE_MAX-1):"<unknown>";
    strncat(logPath,"]", LOG_CATEGORY_PATH_NAME_SIZE_MAX);
    // store it
    strncpy(logNode->_path, logPath, LOG_CATEGORY_PATH_NAME_SIZE_MAX);
    // mark it
    logNode->_isPathInitialized = true;
  }


  // compute file:line
  snprintf(file_line, LOG_FILE_LINE_SIZE, "%s:%04d:", basename_const(ev->fileName), ev->lineNum);

  // compute timestamp
#if !ENABLE_SYS_LOG // remove timestamp for syslog
  char timestamp[TIMESTAMP_SIZE];
  formatTimestamp(timestamp, TIMESTAMP_SIZE);

  // insert timestamp if available
  if (timestamp[0] != NO_TIMESTAMP) {
    SNPRINTF_APPEND(pos, "\n%10s ", timestamp);
  } else {
    SNPRINTF_APPEND(pos, "\n");
  }
#endif

  // compute log file_line header
  SNPRINTF_APPEND(pos, "%-30s[<%-5s>] %-15s ",
                  file_line,
                  logLevelToString(ev->priority),
                  logPathPtr);

  // add function name if needed
  if (ev->printFunctionName) {
     SNPRINTF_APPEND(pos, "%10s() ", ev->functionName);
  }

  // compute log body
  VSNPRINTF_APPEND(pos, ev->fmt, ap);

  // use syslog
#ifdef ENABLE_SYS_LOG
  log_syslog(ev->priority, logMessage);
#endif;

  // push result
  _log(logMessage);

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

} // _log_logEvent


void _log(const char * format, ...) {

  char msg[LOG_MESSAGE_SIZE_MAX];
  va_list ap;

  va_start(ap, format);
  vsnprintf(msg, LOG_MESSAGE_SIZE_MAX, format, ap);
  va_end(ap);

#ifdef ENABLE_STDIO
  // use stdout
  printf("%s", msg);
  fflush(stdout);
#else
  // use fifo
  LogFifoI *fifo = LogFacade::inst().getFifo();
  if( fifo && (fifo->isFull() == false) ) {
    fifo->push(msg);
  }
#endif
}
