#include <stdio.h>
#include <string.h>
#include <stdarg.h>
// placement new operator
#include <new>

#include "log.h"
#include "LogNodeFactory.h"
#include "LogNodeVisitor_ShowTree.h"
#include "LogNodeVisitor_ConfigureLevel.h"

LogNodeFactory &LogNodeFactory::inst() {
  static LogNodeFactory inst;
  return inst;
}

/**
 * Initialize the pre allocated node table
 */
void LogNodeFactory::initTable() {
  LOG_();
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
LogNode *LogNodeFactory::createNode(const char* parent, const char* child) {
  int parentIndex = searchNode(parent);
  int childIndex = searchNode(child);
  LogNode* ret;

  LOG_("%s[%d]->%s[%d]", parent, parentIndex, child, childIndex);

  if (childIndex > 0) {
      ret = &_logNodeTable[childIndex];
  } else {
    if (parentIndex < 0) {
      // create parent first - with root as parent by default
      new (getFreeNode(parentIndex)) LogNode(&(_logNodeTable[0]), parent);
    }
    // create child
    ret = getFreeNode(childIndex);
    new (ret) LogNode(&(_logNodeTable[parentIndex]), child);
  }

#ifdef DEBUG_LOGGER
  printTable();
#endif

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

 // check if  already exit
  for(index=0; index < _logNodeTable_SIZE; index++) {
    if(_logNodeTable[index]._name &&
       strcmp(_logNodeTable[index]._name, nodeName) == 0) {
      ret = index;
    } else if (_logNodeTable[index]._name == 0)
      break;
  }
  return ret;
}

/**
 * Get next free node is node table
 *
 * @param index
 *
 * @return
 */LogNode *LogNodeFactory::getFreeNode(int &index) {
  LogNode * ret = NULL;
  for(index=0; index < _logNodeTable_SIZE; index++) {
    if (_logNodeTable[index]._name == 0) {
      ret= &_logNodeTable[index];
      break;
    }
  }

  //LOG_("index:%d", index);

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
 */
void  LogNodeFactory::configureLevel(const char* confString) {
  printf("\n\nSet spec:%s\n",confString);
  getRootNode()->accept(*(new LogNodeVisitor_ConfigureLevel(confString)));
}

/**
 * Dislay the log tree
 *
 */
void LogNodeFactory::displayLevelTree() {
  printf("\nDisplay spec:\n");
  getRootNode()->accept(*(new LogNodeVisitor_ShowTree));
}

/**
 * Dislay the internal log table (for debug purpose only)
 *
 */
void LogNodeFactory::printTable() {
  int index;
  printf("\n");

  for(index=0; index < _logNodeTable_SIZE; index++) {
    if (_logNodeTable[index]._name == 0) {
      break;
    } else {
      printf("[%d] %s->%s \n", index,
             _logNodeTable[index]._name,
             _logNodeTable[index].getParent()?_logNodeTable[index].getParent()->_name:"-");
        }
  }

}


/**
 * This is the main service of the class:
 *   - create all node pair parent-child as needed to implement
 *     the complete node path given in variadic parameters, started with parent name.
 *   - if only one name is given, the log node is linked to root node as parent
 *
 * @param catNames: a category name or
 *                  a list of category name, started with parent name
 *
 * @return the child node
 */
LogNode * LogNodeFactory::getNode(const char* catName, ...) {

  va_list vl;
  va_start(vl,catName);
  const char* cat = catName;
  const char* parent = LOG_ROOT_NAME;
  LogNode* ret = NULL;

  while (cat) {
    ret = createNode(parent, cat);
    // cumpute next pair (parent, child)
    parent = cat;
    cat = va_arg(vl, const char*);
  }

  va_end(vl);
  return ret;
}
