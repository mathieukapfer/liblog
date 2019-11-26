#include <string.h>
#include "LogConfMem.h"
#include "log_for_logger.h"

ENABLE_LOG(DEBUG);

extern char * LOG_CONF_MEM_PTR;

LogConfMem::LogConfMem() {};

LogConfMem::~LogConfMem() {};

// parse the full configuration data
void LogConfMem::parseConf() {
  char *saveptr;
  char * line = strtok_r(strdup(LOG_CONF_MEM_PTR),"\n", &saveptr);
  char cp ;

  while(line) {
      parseLine(line);
    line = strtok_r(NULL,"\n",&saveptr);
  }
};
