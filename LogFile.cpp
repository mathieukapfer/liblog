#include "LogFile.h"
#include "LogNodeFactory.h"

#define DEBUG_LOGGER
#include "log_macro.h"

void LogFile::parseFile() {
    char buf[LOG_LINE_SIZE_MAX];
    char *str = buf;
    fd = fopen(LOG_CNF_FILE, "r");
    // read line
    if (fd) {
      while (fgets(str, sizeof(buf), fd) != NULL) {
        parseFileLine(buf);
      }
    } else {
      LOG_("file '%s' not found", LOG_CNF_FILE);
    }
}

void LogFile::parseFileLine(char *buf) {
  LOG_("%s",buf)
  LogNodeFactory::inst().configureLevel(buf);
#ifdef DEBUG_LOGGER
  LogNodeFactory::inst().displayLevelTree();
#endif
}
