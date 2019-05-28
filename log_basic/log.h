/**
 * @file   log.h
 * @author Mathieu <mathieu@debian>
 * @date   Fri May 24 11:23:21 2019
 *
 * @brief  This is a standalone logger api with same api of liblog
 *         It can be included in your code without any dependency
 *         The switch to liblog implementation is easy (see libdem sample)
 *
 *         Usage:   LOG_<level>( {param} )
 *            where:
 *                {level}: NONE EMERG FATAL CRIT ERROR WARN NOTIC INFO DEBUG TRACE
 *                {param}: variadic list of parameters like printf()
 *            sample:
 *                  LOG_INFO("this is a log %d",aInt);
 *
 */

#ifndef LOG_H
#define LOG_H

/*
 * DEFINE HERE THE GLOBAL LOG CONFIGURATION SWITCH
 *  => Uncomment this line to remove the log code
 */
// #define LOG_ENABLE

#ifndef LOG_ENABLE

#define LOG_DEBUG(...)
#define LOG_INFO(...)
#define LOG_NOTICE(...)
#define LOG_WARNING(...)
#define LOG_ERROR(...)
#define LOG_FATAL(...)
#define LOG_FORCE(...)
#define LOG_ENTER(...)
#define LOG_EXIT(...)

#define IF_LOG_TRACE
#define IF_LOG_DEBUG
#define IF_LOG_INFO
#define IF_LOG_NOTICE
#define IF_LOG_WARNING
#define IF_LOG_ERROR
#define IF_LOG_CRITICAL
#define IF_LOG_FATAL
#define IF_LOG_EMERGENCY

/* stub of liblog api */
#define LOG_REGISTER(catName, ...)
#define LOG_CONFIGURE(conf);
#define LOG_DISLAY_TREE();

#else

#include <stdio.h>
#include <string.h>
#include <string>

/*
 * DEFINE HERE THE DEFAULT LOG CONFIGURATION
 * or define a local logger specification in your file by copy / past the code below
 * including the '#define LOG_SPEC' line
 */
#ifndef LOG_SPEC
#define LOG_SPEC
#define TEST_LOG_GLOBAL    true
#define TEST_LOG_TRACE     TEST_LOG_GLOBAL && false
#define TEST_LOG_DEBUG     TEST_LOG_GLOBAL && false
#define TEST_LOG_INFO      TEST_LOG_GLOBAL && false
#define TEST_LOG_NOTICE    TEST_LOG_GLOBAL && true
#define TEST_LOG_WARNING   TEST_LOG_GLOBAL && true
#define TEST_LOG_ERROR     TEST_LOG_GLOBAL && true
#define TEST_LOG_CRITICAL  TEST_LOG_GLOBAL && true
#define TEST_LOG_FATAL     TEST_LOG_GLOBAL && true
#define TEST_LOG_EMERGENCY TEST_LOG_GLOBAL && true
#endif

/* macro for log with prefix FILE:LINE */
#define LOG_TRACE(...)     LOG2("TRACE", false, "" ,__VA_ARGS__)
#define LOG_DEBUG(...)     LOG2("DEBUG", false, "" ,__VA_ARGS__)
#define LOG_INFO(...)      LOG2("INFO", false, "" ,__VA_ARGS__)
#define LOG_NOTICE(...)    LOG2("NOTICE", false, "" ,__VA_ARGS__)
#define LOG_WARNING(...)   LOG2("WARNING", false, "" ,__VA_ARGS__)
#define LOG_ERROR(...)     LOG2("ERROR", false, "" ,__VA_ARGS__)
#define LOG_CRITICAL(...)  LOG2("CRITICAL", false, "" ,__VA_ARGS__)
#define LOG_FATAL(...)     LOG2("FATAL", false, "" ,__VA_ARGS__)
#define LOG_EMERGENCY(...) LOG2("EMERGENCY", false, "" ,__VA_ARGS__)

/* macro for log with prefix ENTER|EXIT and FILE:LINE:FUNCTION */
#define LOG_ENTER(...)     LOG2("DEBUG", true,"ENTER:" ,__VA_ARGS__)
#define LOG_EXIT(...)      LOG2("DEBUG", true,"EXIT: " ,__VA_ARGS__)

/* macro to trigger action depend on log level */
#define IF_LOG_TRACE     if(TEST_LOG_TRACE))
#define IF_LOG_DEBUG     if(TEST_LOG_DEBUG))
#define IF_LOG_INFO      if(TEST_LOG_INFO))
#define IF_LOG_NOTICE    if(TEST_LOG_NOTICE))
#define IF_LOG_WARNING   if(TEST_LOG_WARNING))
#define IF_LOG_ERROR     if(TEST_LOG_ERROR))
#define IF_LOG_CRITICAL  if(TEST_LOG_CRITICAL))
#define IF_LOG_FATAL     if(TEST_LOG_FATAL))
#define IF_LOG_EMERGENCY if(TEST_LOG_EMERGENCY))

/* stub of liblog api */
#define LOG_REGISTER(catName, ...)
#define LOG_CONFIGURE(conf);
#define LOG_DISLAY_TREE();

/* formater */
/** \brief Macro to extract file name from __FILE__ */
/** \note The strrchr() function is evaluated at compile time by the gcc compiler */
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define LOG2(level, withFctName, prefixFct, ...)      \
  {                                                   \
    printf("\n%s:%03d:%s %s%s%s",                     \
           __FILENAME__, __LINE__,                    \
           level,                                     \
           withFctName?prefixFct:"",                  \
           withFctName?__FUNCTION__:"",               \
           withFctName?" ":"");                       \
    printf("" __VA_ARGS__);                           \
    fflush(stdout);                                   \
  }

#endif /* LOG_ENABLE */

#endif /* LOG_H */
