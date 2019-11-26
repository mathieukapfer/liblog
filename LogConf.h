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
  // parse line including check
  void parseLine(char *buf);

 private:
  // parse line without check
  void _parseLine(char *buf);

};


#endif /* LOGCONF_H */
