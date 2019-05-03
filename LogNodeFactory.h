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
#ifndef LOG_NO_FILE_SYSTEM
#include "LogFile.h"
#endif

class LogNodeFactory {
 public:

  /// singleton
  static LogNodeFactory &inst();

  /// public api for log node creation
  LogNode *getNode(const char* catName, bool preAllocated, ...);

  /// define log level IN CODE !
  /// NOTE: if LOG_NO_FILE_SYSTEM is false, the file log.cnf is automatically parsed
  bool configureLevel(const char* confString);

  /// dislay log node tree
  void displayLevelTree();

  /// internal api for log node creation
  LogNode *createNode(const char* parent, const char* child, bool preAllocated);

 private:
  LogNodeFactory()
#ifndef LOG_NO_FILE_SYSTEM
    :_logFile(),_isLogFileParsed(false)
#endif
    { initTable(); };
  virtual ~LogNodeFactory() {};

#ifndef LOG_NO_FILE_SYSTEM
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

  /// For debug purpose: print the nodes table
  void printTable();

};



#endif /* LOGNODEFACTORY_H */
