/**
 * @file   log.h
 * @author Mathieu <mathieu@debian>
 * @date   Mon Apr 29 14:09:48 2019
 *
 * @brief  Log your application !
 *
 *  Usage :

    1) In your code,
        - put ONE macro 'LOG_REGISTER(<path>)' by section of code
        - and any LOG_<level>(<param>)
             - <level>:  NONE EMERG FATAL CRIT ERROR WARN NOTIC INFO DEBUG TRACE
             - <param>:  like printf()
    ----------------------------------------------------------------------------

      #include "log.h"
      LOG_REGISTER("MainFile");                <---------- Create a category for the entire file

      int main(int argc, char *argv[]) {
        LOG_REGISTER("Main");                  <---------- Create a sub category 'Main'
        LOG_DEBUG("Hello - in main");          <---------- Log as DEBUG level
          {
            LOG_REGISTER("Main","Section");        <------ Create a sub sub category 'SectionOfMain'
            LOG_INFO("Hello - inside section");    <------ Log as INFO level
          }
        }

       NOTE: LOG_<level>() is like printf() format

    2) Provide log specification
    -----------------------------------------------------------------------------
      2.1) By 'log.cnf' file (in same place as bin)

              # Both level format are supported:
              # Level as str: NONE EMERG FATAL CRIT ERROR WARN NOTIC INFO DEBUG TRACE
              # Level as int: 0,   1,    2,    3,   4,    5,   6,    7,   8,    9

              # put your default level below
              #  by name
              GLOBAL:NOTICE
              #  by int
              GLOBAL:6
              # on a section
              Main.Section:4

      2.2) In code: thanks to 'LOG_CONFIGURE(<path>,<level>)' macro

              LOG_CONFIGURE("Main:2");
              LOG_CONFIGURE("Main.SectionOfMain:3");

      In both case, here is log level meaning:

              TRACE          9  ==> higher verbose level
              DEBUG          8
              INFO           7
              NOTICE         6
              WARNING        5
              ERROR          4
              CRITICAL       3
              FATAL          2
              EMERGENCY      1  ==> lower verbose level
              NONE           0  ==> no log

    3) Get log when you application is running
    -----------------------------------------------------------------------------

log_test.c:0068:         [NOTIC] [Main]                main():Hello - in main: !!!!!
log_test.c:0069:         [NOTIC] [Main]                main():Hello - in main: 999

*/

#ifndef LOG_H
#define LOG_H

#include "log_level.h"
#include "log_macro.h"
#include "LogNodeFactory.h"

/* register a category name to be logged - see note 1) above */
#define LOG_REGISTER(catName, ...)                                     \
  static LogNode *_defaultLogCategory = LogNodeFactory::inst().getNode(catName, false, ##__VA_ARGS__, 0);

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
#define IF_LOG_TRACE if(_LOG_ISENABLED(LP_TRACE))
#define IF_LOG_DEBUG if(_LOG_ISENABLED(LP_DEBUG))
#define IF_LOG_INFO if(_LOG_ISENABLED(LP_INFO))
#define IF_LOG_NOTICE if(_LOG_ISENABLED(LP_NOTICE))
#define IF_LOG_WARNING if(_LOG_ISENABLED(LP_WARNING))
#define IF_LOG_ERROR if(_LOG_ISENABLED(LP_ERROR))
#define IF_LOG_CRITICAL if(_LOG_ISENABLED(LP_CRITICAL))
#define IF_LOG_FATAL if(_LOG_ISENABLED(LP_FATAL))
#define IF_LOG_EMERGENCY if(_LOG_ISENABLED(LP_EMERGENCY))

/* for usage without file system */
/* define log level - BY CODE - see note 2) above */
#define LOG_CONFIGURE(conf)  LogNodeFactory::inst().configureLevel(conf);

/* for support */
/* display log level tree */
#define LOG_DISLAY_TREE() LogNodeFactory::inst().displayLevelTree();

#endif /* LOG_H */
