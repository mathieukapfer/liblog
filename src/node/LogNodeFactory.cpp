//#include <stdio.h>
#include <string.h>
#include <stdarg.h>
// placement new operator
#include <new>

#include "log_for_logger.h"
#include "log_level.h"
#include "LogNodeFactory.h"
#include "LogNodeVisitor_ShowTree.h"
#include "LogSpecParser.h"

#include "ConfigureLevel.h"

ENABLE_LOG(DEBUG);

/**
 * Initialize the pre allocated node table
 */
void LogNodeFactory::initTable() {
  LOG_DEBUG();
  // note: the defauly constructor is aleady called now,
  // just re-create the root node ...
#if 0
  // ... manually
  _logNodeTable[0]._name = LOG_ROOT_NAME;
#else
  // ... by using placement new
  new(&_logNodeTable[0]) LogNode(NULL, LOG_ROOT_NAME, false);
#endif
}

/**
 * Create a child node of given parent
 *
 * @param parent : the parent node
 * @param child  : the name of child node
 *
 * @return the child node
 */
LogNode *LogNodeFactory::createChildNode(LogNode * parent, const char* child, int level, bool preAllocated) {
  LogNode * ret;
  int dummy;
  ret = getFreeNode(dummy);
  if (ret) {
    new (ret) LogNode(parent, child, preAllocated);
    ret->_logLevel = level<0?parent->_logLevel:level;
  }
  LOG_EXIT_("%s->%s:%d", parent->_name, child, ret->_logLevel);
  return ret;
}


/**
 * Create a pair of node parent & child, starting by parent node.
 * NOTE: the node is created only if it do not already exist !
 *
 * @param parent : the name of parent node (i.e. name of log section)
 * @param child  : the name of child node
 *
 * @return the child node
 */
LogNode *LogNodeFactory::createNode(const char* parent, const char* child, bool preAllocated) {
  int parentIndex = searchNode(parent);
  int childIndex = searchNode(child, parent);
  bool creation = false;
  LogNode* ret;

  LOG_DEBUG("%s[%d].%s[%d] (before createNode)", parent, parentIndex, child, childIndex);

  if (childIndex > 0) {
      ret = &_logNodeTable[childIndex];
  } else {
    if (parentIndex < 0) {
      // create parent first - with root as parent by default
      ret = getFreeNode(parentIndex);
      if (ret) {
        new (ret) LogNode(&(_logNodeTable[0]), parent, preAllocated);
        creation = true;
      }
    }
    // create child
    ret = getFreeNode(childIndex);
    if (ret) {
      new (ret) LogNode(&(_logNodeTable[parentIndex]), child, preAllocated);
      creation = true;
    }
  }

  if (ret) {
    if( creation) {
      // just log that
      LOG_INFO("%s[%d].%s[%d]", parent, parentIndex, child, childIndex );
    } else {
      // not created, so update 'preAllocated' flag
      ret->_preAlloacted = preAllocated;
    }
  }

  return ret;
}

/**
 * Search a node with a given name in log table
 *
 * @param nodeName
 *
 * @return -1: no node with the given name exist
 *         >0: the index of node  with the given name
 */
int LogNodeFactory::searchNode(const char* nodeName, const char *parent) {
  int ret = -1;
  int index;

 // check if node already exist
  for(index=0; index < _logNodeTable_SIZE; index++) {
    if(_logNodeTable[index].hasSameName(nodeName)) {
      // check parent if non null or same parent
      if (parent == NULL || _logNodeTable[index].getParent()->hasSameName(parent))  {
        ret = index;
        break;
      }    
    } else if (_logNodeTable[index].isFree()) {
      break;
    }
  }
  //LOG_DEBUG("%s=>%d", nodeName, ret);
  return ret;
}

/**
 * Get next free node is node table
 *
 * @param index
 *
 * @return
 */
LogNode *LogNodeFactory::getFreeNode(int &index) {
  LogNode * ret = NULL;
  for(index=0; index < _logNodeTable_SIZE; index++) {
    if (_logNodeTable[index].isFree()) {
      ret= &_logNodeTable[index];
      break;
    }
  }

  //LOG_DEBUG("index:%d", index);

  if (ret == NULL ){
    LOG_ERROR("no room left for log node!\n");
  }
  return ret;
}


/**
 * Dislay the log tree
 *
 */
void LogNodeFactory::displayLevelTree() {
  _log("\n*Display spec:\n");
  getRootNode()->acceptAll(*(new LogNodeVisitor_ShowTree));
  _log("\n*");
}

/**
 * Dislay the internal log table (for debug purpose only)
 *
 */
void LogNodeFactory::printTable() {
  int index;
  _log("\n");

  for(index=0; index < _logNodeTable_SIZE; index++) {
    if (_logNodeTable[index].isFree()) {
      break;
    } else {
      _log("[%d] %s->%s:%d \n", index,
             _logNodeTable[index]._name,
             _logNodeTable[index].getParent()?_logNodeTable[index].getParent()->_name:"-",
             _logNodeTable[index]._logLevel);
        }
  }

}


/**
 * Define log level for a given path
 *
 * @param confString :the log configuration string like:
 *               "Main:3"
 *               "Main.SectionOfMain:3"
 *               "<LOG_ROOT_NAME>:3"
 * @return if level has been configured (if node exist)
 */
bool LogNodeFactory::configureLevel(const char* confString) {

  static const bool IS_LAST_NAME= true;
  
  LogNode * logNode = getRootNode();
  LogNode * logNodeParent = getRootNode();

  char *currentName;
  int level = -1;
  bool isLastName = false;

  LogSpecParser parser(confString);
  
  // 'GLOBAL' is optional in at the beginning of conf String
  if (parser.isStartingWithRoot() == false) {
    // 'GLOBAL' not present, start with children directly
    logNode =  static_cast<LogNode *>(logNode->getFirstChild());
  }
  
  // search configuration string path in node tree
  while(!isLastName) {

    // get current category name from configuration string
    isLastName =  parser.getNextCatStr(&currentName);
    LOG_INFO(">%s:%d ", currentName, level);    

    if (logNode) {
      // search a sibling node with this name 
      logNode = static_cast<LogNode *>
        (logNode->acceptFirstSibling
         (* (new ConfigureLevel::SearchNodeWithName(currentName))));

      // find it, then continue with the next child
      if(logNode && !isLastName) {
        logNodeParent = logNode;
        logNode = static_cast<LogNode *>(logNode->getFirstChild());
      } else {
        // leave loop
        break;
      }
    }
  } 

  level = parser.getLevel();
  
  if (logNode) {
    LOG_INFO("Node found: '%'s (confString:%s)", logNode->_name, confString);
    // propagate level to all children
    setConfigrationLevel(logNode, level);
  } 
#ifdef ALLOW_CONFIGURATION_BEFORE_DECLARATION
  else {
    LOG_INFO("Node not found with %s (%s) : create it", currentName, confString);

    // create node
    logNodeParent = createChildNode(logNodeParent, currentName, isLastName?level:-1, true);

    //... and continue until end of conf string
    while(!isLastName) { 
      // get next name 
      isLastName =  parser.getNextCatStr(&currentName);
      
      // create node
      logNodeParent = createChildNode(logNodeParent, currentName, isLastName?level:-1, true);
    }
  }
#endif

  return (logNode != NULL);
}


void LogNodeFactory::setConfigrationLevel(LogNode * logNode, int level) {
  LOG_ENTER("%s,%d",logNode->_name, level);
  logNode->acceptAllChildren(* (new ConfigureLevel::SetLevel(level)));
}
