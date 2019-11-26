#include <string.h>
#include "LogConfMem.h"

extern char * LOG_CONF_MEM_PTR;

LogConfMem::LogConfMem() {};

LogConfMem::~LogConfMem() {};

// parse the full configuration data
void LogConfMem::parseConf() {
  char *saveptr;
  char * line = strtok_r(strdup(LOG_CONF_MEM_PTR),"\n", &saveptr);

  while(line) {
    if (line[0] != '#' && strlen(line) > 1) {
      parseLine(line);
    }
    line = strtok_r(NULL,"\n",&saveptr);
  }
};
