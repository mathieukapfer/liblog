#include "log.h"
#include "LogNode.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

/// const
LogNode::LogNode(LogNode *p_parent, const char *p_name):
  Node(p_parent),
  _name(p_name),
  _logLevel(DEFAULT_LOG_LEVEL),
  _inherited(false)
{
  LOG_("LogNode:%s->%s", p_name, p_parent?p_parent->_name:"-");
}


/// default const
LogNode::LogNode():
  Node(),
  _name(NULL),
  _logLevel(DEFAULT_LOG_LEVEL),
  _inherited(false)
{
  LOG_("LogNode (NULL)");
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
