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

#include "log_const.h"
#ifdef LOG_CNF_FILE_ENABLE
#include "LogFile.h"
#endif

// forward declaration
class LogNodeFactory;
class LogNode;

// declaration
class LogFacade {

 public:

  /// singleton
  static LogFacade &inst();

  /// public api for log node creation from variadic
  LogNode *getNode(const char* catName, bool preAllocated, ...);

  /// internal api for log node creation
  LogNode *createNode(const char* parent, const char* child, bool preAllocated);

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

  LogNodeFactory *_logNodeFactory;
#ifdef LOG_CNF_FILE_ENABLE
  LogFile _logFile;
  bool _isLogFileParsed;
#endif

};


#endif /* LOGFACADE_H */