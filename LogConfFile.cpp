#include <string.h>
#include "LogConfFile.h"
#include "LogFacade.h"

#include "log_for_logger.h"

#ifdef ENABLE_COPY_CONF_TO_MEM
// get the pointer to buffer that will cointains the configuration file content
#include "LogConfMem.h"
#endif

ENABLE_LOG(INFO);

LogConfFile::LogConfFile():
  fd(0)
#ifdef ENABLE_COPY_CONF_TO_MEM
  ,_copyOfConfigurationFileInMem(LOG_CONF_MEM_PTR)
#endif
{};

LogConfFile::~LogConfFile() {
  if (fd) {
    fclose(fd);
  }
};

// parse the full configuration data
void LogConfFile::parseConf() {
    char buf[LOG_LINE_SIZE_MAX];
    char *str = buf;
    fd = fopen(LOG_CNF_FILE_NAME, "r");
    LOG_NOTICE("%s %s", LOG_CNF_FILE_NAME, fd>0?"parsing ...":"not found");
    // read line
    if (fd) {
      while (fgets(str, sizeof(buf), fd) != NULL) {
#ifdef ENABLE_COPY_CONF_TO_MEM
          if (_copyOfConfigurationFileInMem != 0)  {
            //LOG_NOTICE("%s", buf);
            strncpy(_copyOfConfigurationFileInMem, buf, LOG_LINE_SIZE_MAX);
            _copyOfConfigurationFileInMem += strnlen(buf, LOG_LINE_SIZE_MAX);
          } else {
            LOG_NOTICE("do not copy to mem (%p)",_copyOfConfigurationFileInMem);
        }
#endif
          parseLine(buf);
      }
    } else {
      LOG_ERROR("file '%s' not found", LOG_CNF_FILE_NAME);
    }
}
