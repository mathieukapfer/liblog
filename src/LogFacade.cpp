#include <stdarg.h>
#include "LogFacade.h"
#include "LogNodeFactory.h"
#include "LogConf.h"
#include "LogNode.h"
#include "LogFifoI.h"

#include "log_const.h"


#ifdef LOG_CNF_FILE_ENABLE
#include "LogConfFile.h"
#else
#include "LogConfMem.h"
#endif

class LogFacade_priv {

 public:
  LogFacade_priv():
    _logNodeFactory(new LogNodeFactory),
#ifdef LOG_CNF_FILE_ENABLE
    _logConf(new LogConfFile()),
#else
    _logConf(new LogConfMem()),
#endif
  _isLogConfParsed(false),
  _fifo(NULL)
  {};
  
  LogNodeFactory *_logNodeFactory;
  LogConf *_logConf;
  bool _isLogConfParsed;
  LogFifoI *_fifo;

};

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

  va_list vl;
  va_start(vl,preAllocated);
  const char* cat = catName;
  const char* parent = LOG_ROOT_NAME;
  LogNode* ret = NULL;

  readConf();

  while (cat) {
    ret = priv->_logNodeFactory->createNode(parent, cat, false);
    // compute next pair (parent, child)
    parent = cat;
    cat = va_arg(vl, const char*);
  }

  va_end(vl);
  return (void *)ret;
}

/// internal api for log node creation
void *LogFacade::createNode(const char* parent, const char* child, bool preAllocated) {
  return (void *)priv->_logNodeFactory->createNode(parent, child, preAllocated);
}


/// Define log level for a given path
bool LogFacade::configureLevel(const char* confString) {
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
bool LogFacade::isLogEnabled(LogNode *catv, int priority) {
  return(catv->_logLevel >= priority);
}

int LogFacade::getLogLevel(LogNode *catv) {
  return(catv->_logLevel);
}
