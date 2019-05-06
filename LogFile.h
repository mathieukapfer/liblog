#ifndef LOGFILE_H
#define LOGFILE_H

#include <stdio.h>
#include "log_const.h"

class LogFile {
 public:
  LogFile():fd(0) {
  };
  virtual ~LogFile() {
    if (fd) {
      fclose(fd);
    }
  };

  void parseFile();

 private:

  // cnf file related method
  FILE* fd;

  void parseFileLine(char *buf);

};



#endif /* LOGFILE_H */
