#include <stdarg.h>

#include "log_facade.h"
#include "LogFacade.h"

void * getNode(const char* catName, int preAllocated, ...) {
  void * ret;
  va_list vl;
  va_start(vl, preAllocated);
  ret = LogFacade::inst().vgetNode(catName, preAllocated, vl);
  va_end(vl);
  return ret;
}

int getLogLevel(void *catv) {
  return LogFacade::inst().getLogLevel((LogNode*) catv);
}

