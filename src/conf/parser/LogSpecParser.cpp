/**
 * @file   LogSpecParser.c
 * @author Mathieu <mathieu@debian>
 * @date   Tue May  7 09:51:46 2019
 *
 * @brief  Stuff to parse configuration string
 *
 *
 */

#include <stdlib.h>
#include <string.h>
#include "log_for_logger.h"
#include "LogSpecParser.h"
#include "log_level.h"

// helper
#define GET_CURRENT_CAT_SIZE parsed.firstCatSize
#define GET_CURRENT_CAT_NAME &_configStr[parsed.firstCatIndex]
#define GET_LEVEL            &_configStr[parsed.levelIndex]


ENABLE_LOG(INFO);

/**
 * Parse the configuration string 
 *
 * @param index           int : current position to parse into the configuration string
 * @param parsed          out : information of parsing:
 *         - firstCatIndex    : offset of the the first category name
 *         - firstCatSize     : size of first category name
 *         - isLastCat        : true if the category name is also the last
 *         - levelIndex       : offset of the level
 */
bool LogSpecParser::parseAtPos(int pos, ConfigStringParsed &parsed) {

  const char *start, *name, *sep, *eq, *level;
  const char *cp = _configStr;

  // move cp to current position
  cp += pos;
  start = cp;

  // remove space bebore name
  cp += strspn(cp, " ");
  name = cp;

  // detect separator position
  cp += strcspn(cp, ".: ");
  sep = cp;

  // detect colon position
  cp += strcspn(cp, ": ");
  eq = cp;

  // move to level
  cp += strspn(cp, ": ");
  level = cp;

  // save it
  _levelStr = level;

  // populate the output
  parsed.firstCatSize  = (sep - name);
  parsed.firstCatIndex = name - start + pos;
  parsed.isLastCat     = (sep == eq);
  parsed.levelIndex    = level - start + pos;

  // move index
  // index += (sep - start) + 1;

  LOG_TRACE("'%s' '%s' %d %d %d",
           GET_CURRENT_CAT_NAME, &_configStr[pos],
           parsed.firstCatSize, parsed.isLastCat, pos);

  return parsed.isLastCat;
}



/// shortcut
bool LogSpecParser::isStartingWithRoot() {
  ConfigStringParsed parsed;
  int localIndex = 0;
  parseAtPos(localIndex, parsed);
  return (memcmp(LOG_ROOT_NAME, GET_CURRENT_CAT_NAME, GET_CURRENT_CAT_SIZE) == 0);
}


/**
 * Provide the current category name of 'configStr' 
 *  and move internal pointer to next category name 
 *  then next called will return the next category
 *
 * @param  firstCat    out : first name  
 * @return true if the last name is reach 
 */
bool LogSpecParser::getNextCatStr(char **cat) {
  ConfigStringParsed parsed;
  int len;

  // parse at current positon
  parseAtPos(_currentIndex, parsed);

  // fill buf with first cat found
  len = min (GET_CURRENT_CAT_SIZE, LOG_CATEGORY_NAME_SIZE_MAX - 1 /* room for '\0' */);
  memcpy(_buf, _configStr + parsed.firstCatIndex, len);
  _buf[len] = '\0';

  *cat = _buf;

  // move index to last position parsed
  _currentIndex = GET_CURRENT_CAT_SIZE + parsed.firstCatIndex + 1;
    
  return parsed.isLastCat;
}

/// parse and return the first category name
bool LogSpecParser::getFirstCatStr(char **cat) {
  // reset the current 
  _currentIndex = 0;
  // call parser
  return getNextCatStr(cat);
}

/// if parsed, then return level value of configuration string
int LogSpecParser::getLevel() {
  int ret;
  
  // check level is present
  if (_levelStr != NULL ) {
    // convert ascii to int
    ret  = atoi(_levelStr);
    if (ret == 0) {
      // convert level string to iny
      ret  = stringToLogLevel( _levelStr );
    }    
  } else {
    ret = -1;
  }
  return ret;
}
