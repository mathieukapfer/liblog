/**
 * @file   LogNodeVisitor_ConfigureLevel.h
 * @author Mathieu <mathieu@debian>
 * @date   Mon Apr 29 15:04:40 2019
 *
 * @brief  Visitor use to dispath a configuration string in node tree
 *
 *
 */
#ifndef LOGNODEVISITOR_CONFIGURELEVEL_H
#define LOGNODEVISITOR_CONFIGURELEVEL_H


#include "LogNode.h"
#include "NodeVisitorI.h"

class LogNodeVisitor_ConfigureLevel: public NodeVisitorI {
 public:
  /// const & dest
  LogNodeVisitor_ConfigureLevel(const char * p_configureString):
    _configureString(p_configureString),
    _currentIndex(0)
    {};
  virtual ~LogNodeVisitor_ConfigureLevel() {};

  /// wrapper to private visitor
  virtual bool visit(Node *node) {
    LogNode *logNode = dynamic_cast<LogNode *>(node);
    return visit(logNode);
  }

  /// action to do during node tree parcour
  virtual void newSibling() {};
  virtual void newChild() {};

 private:

  const char * _configureString;
  int _currentIndex;

  // apply configuration string to current node
  bool visit(LogNode *logNode) ;

  // parse configuration string
  static int parseLevel(const char * _configureString, int &index, const char * nodeName, bool &isFound, bool &checkChild);

};

#endif /* LOGNODEVISITOR_CONFIGURELEVEL_H */
