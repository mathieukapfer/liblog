#include "LogNode.h"
#include <stddef.h>
//#include <stdio.h>
#include <string.h>

#include "log_for_logger.h"
ENABLE_LOG(DEBUG);

/// const
LogNode::LogNode(LogNode *p_parent, const char *p_name, bool p_preAllocated):
  Node(p_parent),
#ifndef ALLOW_CONFIGURATION_BEFORE_DECLARATION
  _name(p_name),
#endif
  _logLevel(p_parent?p_parent->_logLevel:DEFAULT_LOG_LEVEL),
  _inherited(false),
  _preAlloacted(p_preAllocated),
  _isPathInitialized(false)
{
  LOG_DEBUG("LogNode:%s->%s", p_parent?p_parent->_name:"-", p_name);
#ifdef ALLOW_CONFIGURATION_BEFORE_DECLARATION
  strncpy(_name, p_name, LOG_CATEGORY_NAME_SIZE_MAX);
#endif

}


/// default const
LogNode::LogNode():
  Node(),
#ifndef ALLOW_CONFIGURATION_BEFORE_DECLARATION
  _name(NULL),
#endif
  _logLevel(DEFAULT_LOG_LEVEL),
  _inherited(false),
  _isPathInitialized(false)
{
#ifdef ALLOW_CONFIGURATION_BEFORE_DECLARATION
  _name[0] = '\0';
#endif
}

/// is free
bool LogNode::isFree() {
  int ret = false;
#ifdef ALLOW_CONFIGURATION_BEFORE_DECLARATION
  ret = ( _name[0] == '\0');
#else
  ret = (_name == NULL);
#endif
  return ret;
}


/**
 * Get the complete path of log section stared by parents's name
 * Sample:   "Main.Section.SubSection"
 *
 * @param p_fullName : preallocated C string
 * @param p_size     : size of preallocated C string
 *
 * @return : the same 'p_fullName' as input (to easy usage in formater function)
 */
char * LogNode::getFullName(char *p_fullName, int p_size) {
  p_fullName[0] = 0;
  LogNode *node = this;
  while(node->getParent()) {
    char tmp[LOG_CATEGORY_NAME_SIZE_MAX];
    strncpy(tmp, p_fullName, LOG_CATEGORY_NAME_SIZE_MAX);
    snprintf(p_fullName, p_size, "%s%s%s", node->_name, (tmp[0]?".":""), tmp );
    node = node->getParent();
  }
  return p_fullName;
};


bool LogNode::hasSameName(const char* name) {
  LOG_ENTER("%s vs %s",name, _name);
  return (name != NULL && strcmp(_name, name) == 0);
}
