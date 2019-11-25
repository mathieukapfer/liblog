#include <string.h>
#include "LogFacade.h"
#include "log_for_logger.h"

#include "LogConf.h"

ENABLE_LOG(INFO);

void LogConf::parseLine(char *buf) {
  bool namePathIsFound = false;
  LOG_INFO("line:'%s'",buf);
  namePathIsFound = LogFacade::inst().configureLevel(buf);
  LOG_DEBUG("IS %sFOUND:%s\n", namePathIsFound?"":"NOT ", buf) ;
#ifdef DEBUG_LOGGER_ON
  LogNodeFactory::inst().displayLevelTree();
#endif
  LOG_DEBUG("exit %s", buf);
}
