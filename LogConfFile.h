#ifndef LOGFILE_H
#define LOGFILE_H

#include <stdio.h>
#include "log_const.h"
#include "LogConf.h"

class LogConfFile : public LogConf {
 public:

  LogConfFile();
  virtual ~LogConfFile();

  // parse the full configuration data
  virtual void parseConf();

 private:
  void parseFile();

  // cnf file
  FILE* fd;

#ifdef ENABLE_COPY_CONF_TO_MEM
  char * _copyOfConfigurationFileInMem;
#endif

};

#endif /* LOGFILE_H */
