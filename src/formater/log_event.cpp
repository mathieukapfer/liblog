/*
   Format log event and send it
     - to stdout with timestamp  (x86 and a7)
     - to fifo with timestamp    (m3)
     - to syslog without timestamp  (syslog add it own one)

   Samples:

On a7 and x86: timestamp in sec (precision 0,1ms)
 0000.7289 AuthentConfig.cpp:0022:       [<NOTIC>] [AuthentConfig] registerModbusIndex() ENTER:
 0000.7290 MaintenanceDb.cpp:0025:       [<NOTIC>] [MaintenanceDb] registerModbusIndex() ENTER:
 0000.7291 AuthentDb.cpp:0054:           [<NOTIC>] [authen.Db]     registerModbusIndex() ENTER:
 0000.7292 IoCpwIpc.cpp:0040:            [<NOTIC>] [iocpw.ipc]     registerSharedIndex() ENTER:
 0000.7293 IoCpwIpc.cpp:0059:            [<NOTIC>] [iocpw.ipc]     registerModbusIndex() ENTER:

On m3: timestamp = nb tick
  87770 IoCpwConversion_EvState.cpp:0163:[<DEBUG>] [cpwio.evstate] noise:0, max:210, { 0, 0, 0, 0, 0, 0, 210,  }
  87770 IoCpwConversion_EvState.cpp:0167:[<DEBUG>] [cpwio.evstate] EV state: EV_STATE_A_Cpw_Plus12(2) cycle rate:100

On syslog (tail -f /var/log/syslog):
 Oct 21 04:46:33 rzn1-evlink-ep1 evse[256]: CpwDb.cpp:0135:               [<NOTIC>] [cpw.db]        EVState   : EV_STATE_A_Cpw_Plus12(2)
 Oct 21 04:46:33 rzn1-evlink-ep1 evse[256]: ChargeCycle.cpp:0131:         [<NOTIC>] [ChargeCycle]   smState   : ChargingProcedure::Stop
 Oct 21 04:46:33 rzn1-evlink-ep1 evse[256]: ChargeCycle.cpp:0131:         [<NOTIC>] [ChargeCycle]   smState   : EndingProcedure::Start
 Oct 21 04:46:33 rzn1-evlink-ep1 evse[256]: SharedMemory.cpp:0094:        [<NOTIC>] [IPC]           W:SHARED_INDEX_SetCpwIsReady               0 (size:1) @index:11 (offset:44)
 Oct 21 04:46:33 rzn1-evlink-ep1 evse[256]: SharedMemory.cpp:0094:        [<NOTIC>] [IPC]           W:SHARED_INDEX_HMI_API_BLINK               0 (size:1) @index:163 (offset:824)


*/

#include <stdarg.h>
#include <stdio.h>
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

/*
 * local function
 */
void __log(char * msg);
void _log_with_timestamp(const char * format, ...);


/*
 * macro
 */

#define TIMESTAMP_SIZE 10

// uncomment this line to enable stack corruption checker
//#define CHECK_STACK_CORRUPTION

#ifdef CHECK_STACK_CORRUPTION
static const char GUARD_VALUE[]="END!";
#endif

// helper for string filling
#define REMAINING_BUFFER_SIZE(pos) (((LOG_MESSAGE_SIZE_MAX - pos) > 0)?(LOG_MESSAGE_SIZE_MAX - pos):0)
#define SNPRINTF_APPEND(pos, fmt, ...) pos += snprintf(logMessage + pos, REMAINING_BUFFER_SIZE(pos), fmt, ##__VA_ARGS__);
#define VSNPRINTF_APPEND(pos, fmt, ap) pos += vsnprintf(logMessage + pos, REMAINING_BUFFER_SIZE(pos), fmt, ap);

/*
 * code
 */


/*
 * format log event with
 *  - file:line
 *  - log level
 *  - [fonction name for enter/exit log only]
 *  - user message
 * and send it to
 *  - syslog api
 *  - with_timestamp logger (for stdio and buffer output)
 */
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

  // compute log file_line header
  SNPRINTF_APPEND(pos, "%-30s %-5s %-15s ",
                  file_line,
                  logLevelToString(ev->priority),
                  logPathPtr);

  // compute log body
  VSNPRINTF_APPEND(pos, ev->fmt, ap);

  // add function name if needed
  if (ev->printFunctionName) {
     SNPRINTF_APPEND(pos, "%10s() ", ev->functionName);
  }

  // use syslog
#ifdef ENABLE_SYS_LOG
  log_syslog(ev->priority, logMessage);
#endif;

  // push result
  _log_with_timestamp(logMessage);

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

/*
 *  add timestamp and send message to basic logger api
 */
void _log_with_timestamp(const char * format, ...) {

  char logMessage[LOG_MESSAGE_SIZE_MAX];
  va_list ap;
  int pos=0;

  // compute timestamp
  char timestamp[TIMESTAMP_SIZE];
  formatTimestamp(timestamp, TIMESTAMP_SIZE);

  // insert timestamp if available
  if (timestamp[0] != NO_TIMESTAMP) {
    SNPRINTF_APPEND(pos, "%10s ", timestamp);
  }

  // add msg
  va_start(ap, format);
  VSNPRINTF_APPEND(pos, format, ap);
  va_end(ap);

  // \n
  SNPRINTF_APPEND(pos, "\n");

  // send msg
  __log(logMessage);
}


/*
 *  send to basic logger api
 */
void _log(const char * format, ...) {

  char msg[LOG_MESSAGE_SIZE_MAX];
  va_list ap;

  // add msg
  va_start(ap, format);
  vsnprintf(msg, LOG_MESSAGE_SIZE_MAX, format, ap);
  va_end(ap);

  // send msg
  __log(msg);
}

/*
 *  basic logger api that send message
 *  - to stdio (linux)
 *  - to fifo  (freertos)
 */
void __log(char * msg)
{
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
