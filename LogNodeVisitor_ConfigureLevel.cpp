#include <string.h>
#include <stdlib.h>

//#define DEBUG_LOGGER
#include "log.h"
#include "LogNodeVisitor_ConfigureLevel.h"

// apply configuration string to current node
void LogNodeVisitor_ConfigureLevel::visit(LogNode *logNode) {

  int logLevel = -1;
  LogNode *logNodeParent = logNode->getParent();

  LOG_("visit node:%s", logNode->_name);

  // reset inheritage flag
  logNode->_inherited = false;

  // check if parent should inhertied its level
  if (logNodeParent?logNodeParent->_inherited:false) {
    logLevel = logNodeParent->_logLevel;
  } else {
    // parse level
    logLevel = parseLevel(&_configureString[_currentIndex], _currentIndex, logNode->_name);
  }

  // log level really defined ?
  if ( logLevel >= 0 ) {
    // yes, set it
    logNode->_logLevel = logLevel;
    logNode->_inherited = true;
  }

}


/**
 * Parse a configuration string
 *
 * @param configureString: the configuration string like
                           categoty = 1,
                           categoty.subcategory = 1
                           categoty.subcategory.anotherSubCategory = 1
 * @param index            current position to parse into the configuration string
 * @param nodeName         the name of current node
 *
 * @return                 the value of level if node is concerned by the configuration string
 *                         else return -1
 */
int LogNodeVisitor_ConfigureLevel::parseLevel(const char * configureString, int &index, const char * nodeName) {
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
      // set node level
      nodeLevel = atoi(level); // try numeric value
      if(nodeLevel == 0) {
        nodeLevel = stringToLogLevel(level); // try string conversion
      }
      LOG_("set node:%d", nodeLevel);
    } else {
      // move pointer to next name
      index += (sep - configureString) + 1;
      LOG_("move ptr:%d",index);
    }
  }

  LOG_("%s: name:'%-15s'\tdot:'%-10s'\teq:'%-5s'\tlevel:'%-10s'=%d\n=>%d", configureString, name, sep, eq, level, nodeLevel, index);
  return nodeLevel;
}
