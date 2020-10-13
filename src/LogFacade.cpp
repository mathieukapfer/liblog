#include <stdarg.h>
#include "LogFacade.h"
#include "LogFacade_priv.h"

#include "log_for_logger.h"

#include "log_const.h"
ENABLE_LOG(INFO)

LogFacade &LogFacade::inst() {
  static LogFacade inst;
  return inst;
}

LogFacade::LogFacade():
  priv(new LogFacade_priv)
{};

/*
 * refresh log configuration (force read agai)
 */
void LogFacade::refreshConf() {
  priv->_isLogConfParsed = false;
  readConf();
}
/*
 * read conf
 */
void LogFacade::readConf() {
  LOG_ENTER__();
  // parse conf now if needed
  if (priv->_isLogConfParsed == false) {
    priv->_isLogConfParsed = true;
    priv->_logConf->parseConf();
  }
}

/*
 * (re)define at run time the memory addr where the configuration file is copied
 */
#ifdef ENABLE_COPY_CONF_TO_MEM
void LogFacade::registerMemConfAddr(char * newAddr) {
  static_cast<LogConfFile*>(priv->_logConf)->updateMemConfAddr(newAddr);
  refreshConf();
}
#endif

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
void * LogFacade::getNode(const char* catName, bool preAllocated, ...) {

  void* ret = NULL;
  va_list vl;
  va_start(vl,preAllocated);

  ret = vgetNode(catName, preAllocated, vl);

  va_end(vl);
  return (void *) ret;
}

/// public api for log node creation from variadic
void * LogFacade::vgetNode(const char* catName, bool preAllocated, va_list vl) {
  void* ret = NULL;
  const char* cat = catName;
  const char* parent = LOG_ROOT_NAME;

  readConf();

  while (cat) {
    ret = priv->_logNodeFactory->createNode(parent, cat, false);
    // compute next pair (parent, child)
    parent = cat;
    cat = va_arg(vl, const char*);
  }

  return ret;
}


/// Define log level for a given path
bool LogFacade::configureLevel(const char* confString) {
  LOG_ENTER__("*** %s ***",confString);
  return priv->_logNodeFactory->configureLevel(confString);
}


/// dislay log node tree
void LogFacade::displayLevelTree() {
  priv->_logNodeFactory->displayLevelTree();
}


/// api for test
/// todo: put as private and use friend
bool LogFacade::compareLevel(int *tableLevel, int tableSize) {
  return priv->_logNodeFactory->compareLevel(tableLevel, tableSize);
}

/// For debug purpose: print the nodes table
/// todo: put as private and use friend
void LogFacade::printTable() {
  return priv->_logNodeFactory->printTable();
}


/// use fifo instead of stdout
void LogFacade::registerFifo(LogFifoI *fifo) {
  priv->_fifo = fifo;
}

/// getter on fifo
LogFifoI * LogFacade::getFifo() {
  return priv->_fifo;
}


/// getter to log level
int LogFacade::getLogLevel(LogNode *catv) {
  return(catv?catv->_logLevel:0);
}
