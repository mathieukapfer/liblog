/**
 * @file   LogFacade.h
 * @author Mathieu <mathieu@debian>
 * @date   Fri May 10 17:32:00 2019
 *
 * @brief  Public api of log component
 *
 *
 */

#ifndef LOGFACADE_H
#define LOGFACADE_H

// forward declaration
class LogFacade_priv;
class LogNode;
class LogFifoI;

// declaration
class LogFacade {

 public:

  /// singleton
  static LogFacade &inst();

  /// public api for log node creation from variadic
  void *getNode(const char* catName, bool preAllocated, ...);

  /// internal api for log node creation
  void *createNode(const char* parent, const char* child, bool preAllocated);

  /// use fifo instead of stdout
  void registerFifo(LogFifoI *fifo);

  /// getter to fifo
  LogFifoI *getFifo();

  /// getter to log level
  int getLogLevel(LogNode *catv);

  /// refresh log configuration
  void refreshConf();

  /// (re)define at run time the memory addr where the configuration file is copied
#ifdef ENABLE_COPY_CONF_TO_MEM
  void registerMemConfAddr(char * newAddr);
#endif

  /// DO NOT USE THIS IF YOU HAVE "LOG_CNF_FILE_ENABLE"
  /// as the file log.cnf in current directory is automatically parsed
  /// line by line with this method:
  bool configureLevel(const char* confString);

  /// dislay log node tree
  void displayLevelTree();

  /// api for test
  /// todo: put as private and use friend
  bool compareLevel(int *tableLevel, int tableSize);

  /// For debug purpose: print the nodes table
  /// todo: put as private and use friend
  void printTable();

 private:
  LogFacade();
  virtual ~LogFacade() {};

  /// read conf
  void readConf();

  LogFacade_priv *priv;

};


#endif /* LOGFACADE_H */
