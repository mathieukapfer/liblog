/**
 * @file   log.h
 * @author Mathieu <mathieu@debian>
 * @date   Mon Apr 29 14:09:48 2019
 *
 * @brief  Log your application !
 *
 *  Usage :

    1) In your code, put the macro 'LOG_REGISTER(<path>)'
    -----------------------------------------------------

     #include "log.h"
      LOG_REGISTER("Main");                  <---------- Create a category 'Main'
      int main(int argc, char *argv[]) {
        LOG("Hello - in main");
        {
          LOG_REGISTER("Main","SectionOfMain");  <------ Create a sub category 'SectionOfMain'
          LOG("Hello - inside section");
        }
      }

    2) Provide log specification thanks to 'LOG_CONFIGURE(<path>,<level>)' macro
    -----------------------------------------------------------------------------

      LOG_CONFIGURE("Main:2");
      LOG_CONFIGURE("Main.SectionOfMain:3");

      here is log level meaning:

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

    log_test.c      :0011 main     [Main]               :  Hello - in main
    log_test.c      :0014 main     [Main][SectionOfMain]:  Hello - inside section

*/

#ifndef LOG_H
#define LOG_H

#include "log_level.h"
#include "log_macro.h"
#include "LogNodeFactory.h"

/* register a category name to be logged - see note 1) above */
#define LOG_REGISTER(catName, ...)                                     \
  static LogNode *_defaultLogCategory = LogNodeFactory::inst().getNode(catName, ##__VA_ARGS__, 0);

/* Define log level - see note 2) above */
#define LOG_CONFIGURE(conf)  LogNodeFactory::inst().configureLevel(conf);

/* Display log level tree */
#define LOG_DISLAY_TREE() LogNodeFactory::inst().displayLevelTree();

/* Macro for log */
#define LOG_TRACE(fmt, ...)     LOG2(LP_TRACE, "" fmt, ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...)     LOG2(LP_DEBUG, "" fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...)      LOG2(LP_INFO, "" fmt, ##__VA_ARGS__)
#define LOG_NOTICE(fmt, ...)    LOG2(LP_NOTICE, "" fmt, ##__VA_ARGS__)
#define LOG_WARNING(fmt, ...)   LOG2(LP_WARNING, "" fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...)     LOG2(LP_ERROR, "" fmt, ##__VA_ARGS__)
#define LOG_CRITICAL(fmt, ...)  LOG2(LP_CRITICAL, "" fmt, ##__VA_ARGS__)
#define LOG_FATAL(fmt, ...)     LOG2(LP_FATAL, "" fmt, ##__VA_ARGS__)
#define LOG_EMERGENCY(fmt, ...) LOG2(LP_EMERGENCY, "" fmt, ##__VA_ARGS__)

#endif /* LOG_H */
