/**
 * @file   LogNodeFactory.h
 * @author Mathieu <mathieu@debian>
 * @date   Mon Apr 29 14:39:45 2019
 *
 * @brief  This factory of LogNode is the entry point of log component.
 *         It provides the following service
 *          - creation of node log
 *          - configure a log level into the log node tree
 *          - display the log node tree
 */

#ifndef LOGNODEFACTORY_H
#define LOGNODEFACTORY_H

#include "log_const.h"
#include "LogNode.h"
#ifdef LOG_CNF_FILE_ENABLE
#include "LogFile.h"
#endif

class LogNodeFactory {
 public:

  /// singleton
  static LogNodeFactory &inst();

  /// public api for log node creation from variadic
  LogNode *getNode(const char* catName, bool preAllocated, ...);

  /// (re)define log level IN CODE !
  /// NOTE: By defaut, the file log.cnf in current directory is automatically parsed
  bool configureLevel(const char* confString);

  /// dislay log node tree
  void displayLevelTree();

  /// internal api for log node creation
  LogNode *createNode(const char* parent, const char* child, bool preAllocated);

  /// api for test
  /// todo: put as private and use friend
  bool compareLevel(int *tableLevel, int tableSize) {
    bool ret = true;
    for ( int index=0; index < tableSize; index ++) {
      if (_logNodeTable[index]._logLevel != tableLevel[index]) {
          ret = false;
          break;
      }
    }
    return ret;
  }

  /// For debug purpose: print the nodes table
  /// todo: put as private and use friend
  void printTable();

 private:
  LogNodeFactory()
#ifdef LOG_CNF_FILE_ENABLE
    :_logFile(),_isLogFileParsed(false)
#endif
    { initTable(); };
  virtual ~LogNodeFactory() {};

#ifdef LOG_CNF_FILE_ENABLE
  LogFile _logFile;
  bool _isLogFileParsed;
#endif

  /// Factory with pre preallocated table
  ///  in order to allow setup directly on memory
  /// TODO: use generic container (STL) and preallacted table as an option
  static const int _logNodeTable_SIZE = LOG_CATEGORY_NODE_MAX;
  LogNode _logNodeTable[_logNodeTable_SIZE];

  /// Complete the node initialisation by creating the root node at index 0
  void initTable();

  /// Return the table index of the node with name "nodeName". return -1 if not exist
  int searchNode(const char* nodeName);

  /// Get the next free node in node table
  LogNode * getFreeNode(int &index);

  /// Shortcut to get the root node i.e. the first node of the table.
  LogNode *getRootNode() {
    return &_logNodeTable[0];
  }

};



#endif /* LOGNODEFACTORY_H */
