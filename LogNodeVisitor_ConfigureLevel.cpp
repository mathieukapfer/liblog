#include <string.h>
#include <stdlib.h>

#include "log_const.h"
#include "log_for_logger.h"
#include "LogNodeVisitor_ConfigureLevel.h"
#include "LogNodeFactory.h"
#include "parseConfigurationString.h"

ENABLE_LOG(INFO);

// apply configuration string to current node
bool LogNodeVisitor_ConfigureLevel::visit(LogNode *logNode) {

  int logLevel = -1;
  LogNode *logNodeParent = logNode->getParent();
  bool checkChild = false;
  bool isFound = false;

  LOG_INFO("visit node:%s (parent:%s)", logNode->_name, logNodeParent?logNodeParent->_name:"<undef>");

  // reset inheritage flag
  logNode->_inherited = false;

  // check if the child should inherted its level from its parent
  if (logNodeParent?logNodeParent->_inherited:false) {
    logLevel = logNodeParent->_logLevel;
  } else {
    // parse level
    logLevel = parseLevel(_configureString, _currentIndex, logNode->_name, isFound, checkChild);
  }

  // log level really defined ?
  if ( logLevel >= 0 ) {
    LOG_INFO("set %s:%d", logNode->_name, logLevel);
    // yes, set it
    logNode->_logLevel = logLevel;
    // mark the node to inherite its level to all its child
    logNode->_inherited = true;
  }

#ifdef ALLOW_CONFIGURATION_BEFORE_DECLARATION
  LOG_DEBUG("checkChild:%d", checkChild);
  // check child existance now !
  // in order to allow configuration before declaration
  if (checkChild) {
    // if 'checkChild' is true, that mean the node name have been found in
    // configuration string and the index has been move at the beginning of child name
    // so it easy to check the existance of child and create it needed
    char childName[LOG_CATEGORY_NAME_SIZE_MAX];
    getFirstNameStr(&_configureString[_currentIndex], childName);
    LOG_INFO("create prealloacted child:%s", childName);

    LogNodeFactory::inst().createNode(logNode->_name, childName, true);
  }
#endif

  LOG_DEBUG("isFound:%d",isFound);
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

  ConfigStringParsed parsed;
  getFirstName(configureString, index, parsed);
  const char *name  = GET_FIRST_NAME(configureString, parsed);
  const char *level = GET_LEVEL(configureString, parsed);

  // check if the config name is the node name
  if ( (strncmp( nodeName, name, parsed.firstNameSize ) == 0 ) ) {
    if (parsed.isLastName) {
      isFound = true;
      // set node level
      nodeLevel = atoi(level); // try numeric value
      if(nodeLevel == 0) {
        nodeLevel = stringToLogLevel(level); // try string conversion
      }
      LOG_INFO("SET %s:%d", nodeName, nodeLevel);
    } else {
      // move pointer to next name
      checkChild = true;
      index = parsed.firstNameSize + parsed.firstNameIndex + 1;
    }
  }

  return nodeLevel;
}
