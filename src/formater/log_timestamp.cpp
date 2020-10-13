#include "log_timestamp.h"

#ifdef TIMESTAMP_LINUX

/*
 * LINUX api
 */

#include <time.h>
#include <sys/time.h>
#include <stdint.h>
#include <stdio.h>

timeval getTime() {
  timeval actualTime;

#if 0
  gettimeofday(&actualTime, 0);
#else
  timespec ts;
  clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
  actualTime.tv_sec = ts.tv_sec;
  actualTime.tv_usec = ts.tv_nsec / 1000;
#endif

  return actualTime;
}

timeval getTimestamp() {
  timeval actualTime;
  timeval res;

  static timeval startTime = getTime();

  actualTime = getTime();
  timersub(&actualTime, &startTime, &res);

  return res;
}
#else

/*
 * Freertos api
 */

#include <stdio.h>

// function pointer
static uint32_t (*localxTaskGetTickCount)( void ) = 0;

// api to register 'tick count' function
void registerTickCount(uint32_t (*xTaskGetTickCount)( void )) {
  localxTaskGetTickCount = xTaskGetTickCount;
}

#endif

/*
 * Formater
 */

char * formatTimestamp(char * buf, int buf_size) {
#if defined TIMESTAMP_FREERTOS
  if (localxTaskGetTickCount) {
    snprintf(buf, buf_size, "%ld", localxTaskGetTickCount());
  } else {
    buf[0] = NO_TIMESTAMP;
  }
#elif defined TIMESTAMP_LINUX
  timeval ts = getTimestamp();
  snprintf(buf, buf_size, "%04u.%04u", (uint32_t) ts.tv_sec, (uint32_t) ts.tv_usec / 100);
#else
  buf[0] = NO_TIMESTAMP;
#endif
  return buf;
}
