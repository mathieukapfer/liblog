/**
 * @file   LogNode.h
 * @author Mathieu <mathieu@debian>
 * @date   Mon Apr 29 14:28:47 2019
 *
 * @brief  The log node that contains the log section specification,
           mainly the name and the log level (i.e. log trigger)
 */

#ifndef LOGNODE_H
#define LOGNODE_H

#include "node/Node.h"
#include "log_const.h"

class LogNode: public Node {
 public:
  /// const & dest
  LogNode();
  LogNode(LogNode *p_parent, const char *p_name);
  virtual ~LogNode() {};

  /// wrapper to get 'parent()' with right type
  LogNode *getParent() {
    return dynamic_cast<LogNode *>(Node::getParent());
  };

  /// get the complete name stared by parents's name
  char* getFullName(char *p_fullName, int p_size);

  /// is free
  bool isFree();

#ifdef ALLOW_CONFIGURATION_BEFORE_DECLARATION
  char _name[LOG_CATEGORY_NAME_SIZE_MAX];
#else
  const char *_name;
#endif
  int _logLevel;
  bool _inherited;
  bool _preAlloacted;

};

#endif /* LOGNODE_H */