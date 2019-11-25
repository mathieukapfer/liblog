#ifndef LOGCONF_H
#define LOGCONF_H

class LogConf {
 public:
  // const / dest
  LogConf() {};
  virtual ~LogConf() {};

  // parse the full configuration data
  virtual void parseConf() = 0;

 protected:
  // parse one line ended by '\n'
  void parseLine(char *buf);

};


#endif /* LOGCONF_H */
