#include <string.h>
#include <stdlib.h>

#include "log_for_logger.h"
#include "LogNodeVisitor_ConfigureLevel.h"
#include "LogNodeFactory.h"

ENABLE_LOG(INFO);

// apply configuration string to current node
bool LogNodeVisitor_ConfigureLevel::visit(LogNode *logNode) {

  int logLevel = -1;
  LogNode *logNodeParent = logNode->getParent();
  bool checkChild = false;
  bool isFound = false;

  LOG_("visit node:%s (parent:%s)", logNode->_name, logNodeParent?logNodeParent->_name:"<undef>");

  // reset inheritage flag
  logNode->_inherited = false;

  // check if the child should inherted its level from its parent
  if (logNodeParent?logNodeParent->_inherited:false) {
    logLevel = logNodeParent->_logLevel;
  } else {
    // parse level
    logLevel = parseLevel(&_configureString[_currentIndex], _currentIndex, logNode->_name, isFound, checkChild);
  }

  // log level really defined ?
  if ( logLevel >= 0 ) {
    // yes, set it
    logNode->_logLevel = logLevel;
    // mark the node to inherite its level to all its child
    logNode->_inherited = true;
  }

#ifdef ALLOW_CONFIGURATION_BEFORE_DECLARATION
  // check child existance now !
  // in order to allow configuration before declaration
  if (checkChild) {
    // if 'checkChild' is true, that mean the node name have been found in configuration string
    // and the index has been move at the beginning of child name
    // so it easy to check the existance of child and create it needed
    const char * cp = &_configureString[_currentIndex];
    char childName[LOG_CATEGORY_NAME_SIZE_MAX];
    int childNameSize = strcspn(cp, ".: ");

    LOG_("CHILD START:%s - size:%d", cp, childNameSize);
    strncpy(childName, cp, childNameSize);
    childName[childNameSize] = '\0';

    LogNodeFactory::inst().createNode(logNode->_name, childName, true);
  }
#endif

  LOG_("isFound:%d",isFound);
  return isFound;

}


/**
 * Parse a configuration string
 *
 * @param configureString: the configuration string like
                           "category = 1",
                           "category.subcategory = 1"
                           "category.subcategory.anotherSubCategory = 1"
 * @param index            current position to parse into the configuration string
 * @param nodeName         the name of current node
 *
 * @return                 the value of level if node is concerned by the configuration string
 *                         else return -1
 */
int LogNodeVisitor_ConfigureLevel::parseLevel(const char * configureString, int &index, const char * nodeName, bool &isFound, bool &checkChild) {
  int nodeLevel = -1;
  const char *name, *sep, *eq, *level;
  const char *cp = configureString;
  // remove space bebore name
  cp += strspn(cp, " ");
  name = cp;
  // detect separator position
  cp += strcspn(cp, ".: ");
  sep = cp;
  // detect colon position
  cp += strcspn(cp, ": ");
  eq = cp;
  // move to level
  cp += strspn(cp, ": ");
  level = cp;

  // check if name is the node name
  if ( (strncmp( nodeName, name, sep - name ) == 0 ) ) {
    // if 'sep' contains a colon, then we reach the last category
    if (sep == eq) {
      isFound = true;
      // set node level
      nodeLevel = atoi(level); // try numeric value
      if(nodeLevel == 0) {
        nodeLevel = stringToLogLevel(level); // try string conversion
      }
      LOG_("set node:%d", nodeLevel);
    } else {
      // move pointer to next name
      index += (sep - configureString) + 1;
      LOG_("move ptr:+%d",index);
      checkChild = true;
    }
  }

  LOG_("%s: name:'%-15s'\tdot:'%-10s'\teq:'%-5s'\tlevel:'%-10s'=%d\n=>%d", configureString, name, sep, eq, level, nodeLevel, index);
  return nodeLevel;
}
