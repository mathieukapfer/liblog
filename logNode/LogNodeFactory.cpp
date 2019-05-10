#include <stdio.h>
#include <string.h>
#include <stdarg.h>
// placement new operator
#include <new>

#include "log_for_logger.h"
#include "log_level.h"
#include "LogNodeFactory.h"
#include "LogNodeVisitor_ShowTree.h"
#include "LogNodeVisitor_ConfigureLevel.h"
#include "parseConfigurationString.h"

ENABLE_LOG(INFO);

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
  new(&_logNodeTable[0]) LogNode(NULL, LOG_ROOT_NAME);
#endif
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
  int childIndex = searchNode(child);
  bool creation = false;
  LogNode* ret;

  LOG_INFO("%s[%d]->%s[%d]", child, childIndex, parent, parentIndex);

  if (childIndex > 0) {
      ret = &_logNodeTable[childIndex];
  } else {
    if (parentIndex < 0) {
      // create parent first - with root as parent by default
      new (getFreeNode(parentIndex)) LogNode(&(_logNodeTable[0]), parent);
      creation = true;
    }
    // create child
    ret = getFreeNode(childIndex);
    new (ret) LogNode(&(_logNodeTable[parentIndex]), child);
    creation = true;
  }

  if (creation) {
    if (preAllocated == true) {
      // mark node as prealloacted
      ret->_preAlloacted = true;
    } else {
      // creation by declaration => set default level as root level
      ret->_logLevel = getRootNode()->_logLevel;
    }
    LOG_INFO("%s[%d]->%s[%d]", child, childIndex, parent, parentIndex);
  } else {
    if (preAllocated == false) {
      // reset flag
      ret->_preAlloacted = false;
    }
    //LOG_DEBUG("aleady done");
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
int LogNodeFactory::searchNode(const char* nodeName) {
  int ret = -1;
  int index;

 // check if already exit
  for(index=0; index < _logNodeTable_SIZE; index++) {
    if(_logNodeTable[index]._name &&
       strcmp(_logNodeTable[index]._name, nodeName) == 0) {
      ret = index;
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
    printf("no room left for log node!\n");
  }
  return ret;
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
bool  LogNodeFactory::configureLevel(const char* confString) {
  bool ret = false;
  LOG_DEBUG("%s",confString);

  // add prefix 'GLOBAL.' if not present
  bool useNewConfStr = false;
  char firstName[LOG_CATEGORY_NAME_SIZE_MAX];
  char newConfstr[LOG_CATEGORY_PATH_NAME_SIZE_MAX] =  { '\0' };

  if (strcmp(LOG_ROOT_NAME, getFirstNameStr(confString, firstName)) != 0) {
    strncat(newConfstr, LOG_ROOT_NAME, LOG_CATEGORY_PATH_NAME_SIZE_MAX);
    strncat(newConfstr, ".", LOG_CATEGORY_PATH_NAME_SIZE_MAX);
    strncat(newConfstr, confString, LOG_CATEGORY_PATH_NAME_SIZE_MAX);
    useNewConfStr = true;
    LOG_INFO("firstName:%s => conf:%s", firstName, newConfstr);
  }

  // launch configuation level visitor
  ret = (getRootNode()->accept
         (*(new LogNodeVisitor_ConfigureLevel (useNewConfStr?newConfstr:confString))));

  // log if found
  LOG_DEBUG("'%s' %s",confString, ret?"found":"NOT FOUND");
  IF_LOG_INFO {
    displayLevelTree();
  }

  return ret;
}

/**
 * Dislay the log tree
 *
 */
void LogNodeFactory::displayLevelTree() {
  printf("\nDisplay spec:\n");
  getRootNode()->accept(*(new LogNodeVisitor_ShowTree));
  printf("\n");
}

/**
 * Dislay the internal log table (for debug purpose only)
 *
 */
void LogNodeFactory::printTable() {
  int index;
  printf("\n");

  for(index=0; index < _logNodeTable_SIZE; index++) {
    if (_logNodeTable[index].isFree()) {
      break;
    } else {
      printf("[%d] %s->%s:%d \n", index,
             _logNodeTable[index]._name,
             _logNodeTable[index].getParent()?_logNodeTable[index].getParent()->_name:"-",
             _logNodeTable[index]._logLevel);
        }
  }

}
