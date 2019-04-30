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

class LogNodeFactory {
 public:

  /// singleton
  static LogNodeFactory &inst();

  /// public api for log node creation
  LogNode *getNode(const char* catName, ...);

  /// define log level
  void configureLevel(const char* confString);

  /// dislay log node tree
  void displayLevelTree();

 private:
  LogNodeFactory() { initTable(); };
  virtual ~LogNodeFactory() {};

  /// Factory with pre preallocated table
  ///  in order to allow setup directly on memory
  /// TODO: use generic container (STL) and preallacted table as an option
  static const int _logNodeTable_SIZE = LOG_CATEGOTY_NODE_MAX;
  LogNode _logNodeTable[_logNodeTable_SIZE];

  /// Complete the node initialisation by creating the root node at index 0
  void initTable();

  /// Create a child node linked to its parent - create the parent if needed
  LogNode *createNode(const char* parent, const char* child);

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
