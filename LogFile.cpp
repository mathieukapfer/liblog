#include <string.h>
#include "LogFile.h"
#include "LogFacade.h"

#include "log_for_logger.h"
ENABLE_LOG(INFO);

void LogFile::parseFile() {
    char buf[LOG_LINE_SIZE_MAX];
    char *str = buf;
    fd = fopen(LOG_CNF_FILE_NAME, "r");
    LOG_NOTICE("%s %s", LOG_CNF_FILE_NAME, fd>0?"parsing ...":"not found");
    // read line
    if (fd) {
      while (fgets(str, sizeof(buf), fd) != NULL) {
        if (buf[0] != '#' && strlen(buf) > 1) {
          //LOG_INFO("line: %s",buf);
          parseFileLine(buf);
        }
      }
    } else {
      LOG_ERROR("file '%s' not found", LOG_CNF_FILE_NAME);
    }
}

void LogFile::parseFileLine(char *buf) {
  bool namePathIsFound = false;
  LOG_INFO("line:'%s'",buf);
  namePathIsFound = LogFacade::inst().configureLevel(buf);
  LOG_DEBUG("IS %sFOUND:%s\n", namePathIsFound?"":"NOT ", buf) ;
#ifdef DEBUG_LOGGER_ON
  LogNodeFactory::inst().displayLevelTree();
#endif
  LOG_DEBUG("exit %s", buf);
}
