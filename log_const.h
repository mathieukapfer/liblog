/**
 * @file   log_const.h
 * @author Mathieu <mathieu@debian>
 * @date   Mon Apr 29 14:05:12 2019
 *
 * @brief  Put here all magic numbers of log component
 *
 *
 */

#ifndef LOG_CONST_H
#define LOG_CONST_H

// name of root node
#define LOG_ROOT_NAME "GLOBAL"

// default log level
#define DEFAULT_LOG_LEVEL 6

// max size of a category
#define LOG_CATEGORY_NAME_SIZE_MAX 40

// max size of a full path of category
#define LOG_CATEGORY_PATH_NAME_SIZE_MAX 100

// size of pre allocated table of node
#define LOG_CATEGORY_NODE_MAX 50

// option
#define ALLOW_CONFIGURATION_BEFORE_DECLARATION


#endif /* LOG_CONST_H */
