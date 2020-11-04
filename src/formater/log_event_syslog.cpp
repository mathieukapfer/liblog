#include <syslog.h>
#include "log_facade.h"

// keep volatile qualifier for cross compilation (needed by M3)
#ifdef __arm__
#define VOLATILE volatile
#else
#define VOLATILE
#endif

static VOLATILE void *_defaultLogCategory = (void *) getNode("SYSLOG_MAX_LEVEL", false, 0);
static VOLATILE bool isSyslogOpened = false;

#define MAX(a,b) (a)>(b)?(a):(b)

void log_syslog(int prio, const char * msg) {

  // note that "log prio - 1" is aligned with syslog level

  // init logger
  if (!isSyslogOpened) {
    // compute 'log_level' minus 1,
    // but take care '0' that mean's NO LOG for our logger
    int log_mask = MAX(getLogLevel((void *)_defaultLogCategory)-1 , 0);
    setlogmask (LOG_UPTO(log_mask));
    openlog("evse", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
    isSyslogOpened = true;
  }

  // push log
  syslog(prio - 1, "%s", msg);
}
