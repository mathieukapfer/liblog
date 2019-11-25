#ifndef LOGCONFMEM_H
#define LOGCONFMEM_H

class LogConfMem: public LogConf {

 public:
  LogConfMem();
  virtual ~LogConfMem();

  // parse the full configuration data
  virtual void parseConf();

};



#endif /* LOGCONFMEM_H */
