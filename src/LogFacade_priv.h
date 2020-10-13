#ifndef LOGFACADEPRIV_H
#define LOGFACADEPRIV_H

#include "LogNodeFactory.h"
#include "LogConf.h"
#include "LogNode.h"
#include "LogFifoI.h"

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



#endif /* LOGFACADEPRIV_H */