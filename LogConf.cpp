#include <string.h>
#include "LogFacade.h"
#include "log_for_logger.h"
#include "log_const.h"
#include "LogConf.h"

ENABLE_LOG(INFO);

void LogConf::parseLine(char *buf) {

  char *line = NULL;

  // check if line is not too big
  if ( strnlen(buf, LOG_LINE_SIZE_MAX) !=  LOG_LINE_SIZE_MAX) {

    // remove space before
    buf += strspn(buf, " \t");

    // remove comment and line too short
    if ( (buf[0] != '#') && (strlen(buf) > 1) ){
        _parseLine(buf);
    }
  }

}

void LogConf::_parseLine(char *buf) {
  bool namePathIsFound = false;
  LOG_INFO("line:'%s'",buf);
  namePathIsFound = LogFacade::inst().configureLevel(buf);
  LOG_DEBUG("IS %sFOUND:%s\n", namePathIsFound?"":"NOT ", buf) ;

#ifdef DEBUG_LOGGER_ON
  LogNodeFactory::inst().displayLevelTree();
#endif

  LOG_DEBUG("exit %s", buf);
}
