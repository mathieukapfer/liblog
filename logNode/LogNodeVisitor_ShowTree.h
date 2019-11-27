/**
 * @file   LogNodeVisitor_ShowTree.h
 * @author Mathieu <mathieu@debian>
 * @date   Mon Apr 29 15:11:22 2019
 *
 * @brief  Visitor to display the log node tree
 *
 *
 */

#ifndef LOGNODEVISITOR_SHOWTREE_H
#define LOGNODEVISITOR_SHOWTREE_H

//#include <stdio.h>

#include "LogNode.h"
#include "NodeVisitorI.h"


class LogNodeVisitor_ShowTree: public NodeVisitorI {
 public:
  LogNodeVisitor_ShowTree() {};
  virtual ~LogNodeVisitor_ShowTree() {};

  virtual bool visit(Node *node) {
    LogNode *logNode = static_cast<LogNode *>(node);
    return visit(logNode);
  }

  virtual void newSibling() {_log("\n");};
  virtual void newChild() {_log("\n");};

 private:

  bool visit(LogNode *logNode) {
    char buf[LOG_CATEGORY_PATH_NAME_SIZE_MAX];
    (logNode)->getFullName(buf,LOG_CATEGORY_PATH_NAME_SIZE_MAX);

    _log(" %-25s:%s(%d) %s",
           buf[0]?buf:"GLOBAL",
           logLevelToString(logNode->_logLevel),
           logNode->_logLevel,
           logNode->_preAlloacted?"// prealloacted":""
      );
    // always return true in this case
    return true;
  }

};



#endif /* LOGNODEVISITOR_SHOWTREE_H */
