/**
 * @name Priority Values
 *
 * These are the same names (except TRACE is new) as used by Unix syslog(), but
 * the numerical values are different.
 *@{
 */

#ifndef LOG_LEVEL_H
#define LOG_LEVEL_H

#define LP_NONE           0
#define LP_EMERGENCY      1
#define LP_FATAL          2
#define LP_CRITICAL       3
#define LP_ERROR          4
#define LP_WARNING        5
#define LP_NOTICE         6
#define LP_INFO           7
#define LP_DEBUG          8
#define LP_TRACE          9

const char * logLevelToString(int level);
int stringToLogLevel(const char *  levelStr);

#endif /* LOG_LEVEL_H */
