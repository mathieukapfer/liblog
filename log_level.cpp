#include <string.h>
#include "log_level.h"

#define LP_MAX LP_TRACE

static const char* logLevelString[LP_MAX+1] = {
  "NONE",
  "EMERG",
  "FATAL",
  "CRIT",
  "ERROR",
  "WARN",
  "NOTIC",
  "INFO",
  "DEBUG",
  "TRACE"
};

const char * logLevelToString(int level) {
  const char *ret = "<NDEF>";
  if (level <= LP_MAX) {
    ret = logLevelString[level];
  }
  return ret;
}

int stringToLogLevel(const char *  levelStr) {
  int ret = 0;
  bool isFound = false;
  for (ret = 0; ret < LP_MAX; ret++) {
    if (strncmp(logLevelString[ret], levelStr, strlen(logLevelString[ret])) == 0) {
      isFound = true;
      break;
    }
  }
  return isFound?ret:0;
}
