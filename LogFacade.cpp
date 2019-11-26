#include <stdarg.h>
#include "LogFacade.h"
#include "LogNodeFactory.h"

#ifdef LOG_CNF_FILE_ENABLE
#include "LogConfFile.h"
#else
#include "LogConfMem.h"
#endif


LogFacade &LogFacade::inst() {
  static LogFacade inst;
  return inst;
}


LogFacade::LogFacade():
  _logNodeFactory(new LogNodeFactory),
#ifdef LOG_CNF_FILE_ENABLE
  _logConf(* new LogConfFile()),
#else
  _logConf(* new LogConfMem()),
#endif
  _isLogConfParsed(false),
  _fifo(NULL)
    {};

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
LogNode * LogFacade::getNode(const char* catName, bool preAllocated, ...) {

  va_list vl;
  va_start(vl,preAllocated);
  const char* cat = catName;
  const char* parent = LOG_ROOT_NAME;
  LogNode* ret = NULL;

  // parse Conf now if needed
  if (_isLogConfParsed == false) {
    _isLogConfParsed = true;
    _logConf.parseConf();
  }

  while (cat) {
    ret = _logNodeFactory->createNode(parent, cat, false);
    // cumpute next pair (parent, child)
    parent = cat;
    cat = va_arg(vl, const char*);
  }

  va_end(vl);
  return ret;
}

/// internal api for log node creation
LogNode *LogFacade::createNode(const char* parent, const char* child, bool preAllocated) {
  return _logNodeFactory->createNode(parent, child, preAllocated);
}


/// Define log level for a given path
bool LogFacade::configureLevel(const char* confString) {
  return _logNodeFactory->configureLevel(confString);
}

/// dislay log node tree
void LogFacade::displayLevelTree() {
  _logNodeFactory->displayLevelTree();
}


/// api for test
/// todo: put as private and use friend
bool LogFacade::compareLevel(int *tableLevel, int tableSize) {
  return _logNodeFactory->compareLevel(tableLevel, tableSize);
}

/// For debug purpose: print the nodes table
/// todo: put as private and use friend
void LogFacade::printTable() {
  return _logNodeFactory->printTable();
}


/// use fifo instead of stdout
void LogFacade::registerFifo(LogFifoI *fifo) {
  _fifo = fifo;
}

/// getter on fifo
LogFifoI * LogFacade::getFifo() {
  return _fifo;
}
