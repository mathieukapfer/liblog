#ifndef LOGCONFMEM_H
#define LOGCONFMEM_H

#include "LogConf.h"

class LogConfMem: public LogConf {

 public:
  LogConfMem();
  virtual ~LogConfMem();

  // parse the full configuration data
  virtual void parseConf();

};



#endif /* LOGCONFMEM_H */
