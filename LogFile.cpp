#include <string.h>
#include "LogFile.h"
#include "LogNodeFactory.h"

#include "log_for_logger.h"
ENABLE_LOG(INFO);

void LogFile::parseFile() {
    char buf[LOG_LINE_SIZE_MAX];
    char *str = buf;
    fd = fopen(LOG_CNF_FILE, "r");
    // read line
    if (fd) {
      while (fgets(str, sizeof(buf), fd) != NULL) {
        if (buf[0] != '#' && strlen(buf) > 1) {
          parseFileLine(buf);
        }
      }
    } else {
      printf("file '%s' not found", LOG_CNF_FILE);
    }
}

void LogFile::parseFileLine(char *buf) {
  bool namePathIsFound = false;
  LOG_("%s",buf)
  namePathIsFound = LogNodeFactory::inst().configureLevel(buf);
  LOG_("IS %sFOUND:%s\n", namePathIsFound?"":"NOT ", buf) ;
#ifdef DEBUG_LOGGER_ON
  LogNodeFactory::inst().displayLevelTree();
#endif
  LOG_("exit %s", buf);
}
