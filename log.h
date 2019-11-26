/**
 * @file   log.h
 * @author Mathieu <mathieu@debian>
 * @date   Mon Apr 29 14:09:48 2019
 *
 * @brief  Log your application ! - see README.md
 */

#ifndef LOG_H
#define LOG_H

#include "log_level.h"
#include "log_macro.h"
#include "LogFacade.h"

#ifndef ENABLE_STDIO
// no stdio, so provide fifo
#include "LogFifo.h"
#endif

// keep volatile qualifier for cross compilation (needed by M3, check if needed by A7)
//#ifndef __i386__
#ifdef __arm__
#define VOLATILE volatile
#else
#define VOLATILE
#endif

/* register a category name to be logged - see note 1) above */
#define LOG_REGISTER(catName, ...)                                     \
  static VOLATILE  LogNode *_defaultLogCategory = LogFacade::inst().getNode(catName, false, ##__VA_ARGS__, 0);

/* macro for log */
#define LOG_TRACE(fmt, ...)     LOG2(LP_TRACE, false, "" fmt, ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...)     LOG2(LP_DEBUG, false,"" fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...)      LOG2(LP_INFO, false, "" fmt, ##__VA_ARGS__)
#define LOG_NOTICE(fmt, ...)    LOG2(LP_NOTICE, false,"" fmt, ##__VA_ARGS__)
#define LOG_WARNING(fmt, ...)   LOG2(LP_WARNING, false,"" fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...)     LOG2(LP_ERROR, false,"" fmt, ##__VA_ARGS__)
#define LOG_CRITICAL(fmt, ...)  LOG2(LP_CRITICAL, false,"" fmt, ##__VA_ARGS__)
#define LOG_FATAL(fmt, ...)     LOG2(LP_FATAL, false,"" fmt, ##__VA_ARGS__)
#define LOG_EMERGENCY(fmt, ...) LOG2(LP_EMERGENCY, false,"" fmt, ##__VA_ARGS__)

/* same as above but with function name and prefix ENTER / EXIT*/
#define LOG_ENTER(fmt, ...)             LOG2(LP_DEBUG, true,"ENTER:" fmt, ##__VA_ARGS__)
#define LOG_EXIT(fmt, ...)              LOG2(LP_DEBUG, true,"EXIT: " fmt, ##__VA_ARGS__)

/* macro to trigger action depend on log level */
#define IF_LOG_TRACE if(_LOG_ISENABLED(_defaultLogCategory, LP_TRACE))
#define IF_LOG_DEBUG if(_LOG_ISENABLED(_defaultLogCategory, LP_DEBUG))
#define IF_LOG_INFO if(_LOG_ISENABLED(_defaultLogCategory, LP_INFO))
#define IF_LOG_NOTICE if(_LOG_ISENABLED(_defaultLogCategory, LP_NOTICE))
#define IF_LOG_WARNING if(_LOG_ISENABLED(_defaultLogCategory, LP_WARNING))
#define IF_LOG_ERROR if(_LOG_ISENABLED(_defaultLogCategory, LP_ERROR))
#define IF_LOG_CRITICAL if(_LOG_ISENABLED_defaultLogCategory,LP_CRITICAL))
#define IF_LOG_FATAL if(_LOG_ISENABLED(_defaultLogCategory, LP_FATAL))
#define IF_LOG_EMERGENCY if(_LOG_ISENABLED(_defaultLogCategory, LP_EMERGENCY))

/* for usage without file system */
/* define log level - BY CODE - see note 2) above */
#define LOG_CONFIGURE(conf)  LogFacade::inst().configureLevel(conf);

/* for support */
/* display log level tree */
#define LOG_DISLAY_TREE() LogFacade::inst().displayLevelTree();

/* for fifo instread of stdio */
#define LOG_REGISTER_FIFO(fifo) LogFacade::inst().registerFifo(fifo);

/* provide at complation time the memory addr where the configuration file will be copied
 * (this is use for instance to share the conf from A7[Linux] to M3[Freertos] in LCES2 platform)
 */
#ifdef ENABLE_COPY_CONF_TO_MEM
#define LOG_REGISTER_MEM_CONF_ADDR(addr) LogFacade::inst().registerMemConfAddr(addr)
#endif

#endif /* LOG_H */
