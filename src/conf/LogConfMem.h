#ifndef LOGCONFMEM_H
#define LOGCONFMEM_H

#include "LogConf.h"

// this is the location of configuration strings buffer
extern char * LOG_CONF_MEM_PTR;

class LogConfMem: public LogConf {

 public:
  LogConfMem();
  virtual ~LogConfMem();

  // parse the full configuration data
  virtual void parseConf();

};



#endif /* LOGCONFMEM_H */
