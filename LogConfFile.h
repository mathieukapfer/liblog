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

  // cnf file related method
  FILE* fd;

};

#endif /* LOGFILE_H */
