/**
 * @file   parseConfString.c
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
#include "parseConfString.h"
#include "log_level.h"

ENABLE_LOG(INFO);

/**
 * Parse the configuration string to extract the first name
 *
 * @param configureString         The configuration string, can be:
                                  "category = 1",
                                  "category.subcategory = 1"
                                  "category.subcategory.anotherSubCategory = 1"
 * @param index                   current position to parse into the configuration string
 * @param parsed.firstNameIndex   offset of the the first name
 * @param parsed.firstNameSize    size of first name
 * @param parsed.isLastName       true if the name is also the last
 * @param parsed.levelIndex       offset of the level if we reach the last name
 */
bool getFirstName(const char * configureString, int &index, ConfigStringParsed &parsed) {

  const char *start, *name, *sep, *eq, *level;
  const char *cp = configureString;

  // move cp to current position
  cp += index;
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

  // populate the output
  parsed.firstNameSize = (sep - name);
  parsed.firstNameIndex = name - start + index;
  parsed.isLastName = (sep == eq);
  parsed.levelIndex = level - start + index;

  // move index
  // index += (sep - start) + 1;

  LOG_INFO("'%s' '%s' %d %d %d",
           &configureString[ parsed.firstNameIndex], &configureString[index],
           parsed.firstNameSize, parsed.isLastName, index);

  return parsed.isLastName;
}


/**
 * Fillup the first category name of 'configStr'
 *
 * @param configStr
 * @param firstName
 *
 * @return
 */
char *getFirstNameStr(const char *configStr , char *firstName) {
  ConfigStringParsed parsed;
  int localIndex = 0;
  getFirstName(configStr, localIndex, parsed);
  strncpy(firstName, configStr + parsed.firstNameIndex,
          min (parsed.firstNameSize, LOG_CATEGORY_NAME_SIZE_MAX ));
  firstName[parsed.firstNameSize] = '\0';
  return firstName;
}

/// shortcut
bool isFirstName_RootName(const char *configStr) {
  ConfigStringParsed parsed;
  int localIndex = 0;
  getFirstName(configStr, localIndex, parsed);
  return (memcmp(LOG_ROOT_NAME,
                 &configStr[parsed.firstNameIndex],
                 parsed.firstNameSize) == 0);
}


/**
 * Fillup the first category name of 'configStr'
 *
 * @param configStr    in     : the config string to parse
 * @param firstName    in out : buffer to receive the copy of first name of config string 
 * @param level        out    : level of config string if last last name is reach, else -1
 * @param currentIndex in out : keep trace of last position parsed in confiug string
 *
 * @return true if the last name is reach - in this case, level is also parsed
 */
bool getFirstNameStr_(const char *configStr , char *firstName, int &level, int &currentIndex) {
  ConfigStringParsed parsed;

  // parse config string
  getFirstName(configStr, currentIndex, parsed);

  // put a copy of string in given buffer 
  strncpy(firstName, configStr + parsed.firstNameIndex,
          min (parsed.firstNameSize, LOG_CATEGORY_NAME_SIZE_MAX ));
  
  firstName[parsed.firstNameSize] = '\0';

  // rewind to last position parsed
  currentIndex = parsed.firstNameSize + parsed.firstNameIndex + 1;

  // parse level is last name reach
  if (parsed.isLastName) {
    level = atoi(&configStr[parsed.levelIndex]);
    if (level == 0) {
      level = stringToLogLevel( &configStr[parsed.levelIndex] );
    }
  } else {
    level = -1;
  }
  
  return parsed.isLastName;
}
