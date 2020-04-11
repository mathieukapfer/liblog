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

ENABLE_LOG(NOTICE);

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


/**
 * Fillup the first category name of 'configStr'
 *
 * @param configStr
 * @param firstName
 *
 * @return
 */
int getFirstNameStr_(const char *configStr , char *firstName, int &currentIndex) {
  ConfigStringParsed parsed;

  getFirstName(configStr, currentIndex, parsed);
  
  strncpy(firstName, configStr + parsed.firstNameIndex,
          min (parsed.firstNameSize, LOG_CATEGORY_NAME_SIZE_MAX ));
  
  firstName[parsed.firstNameSize] = '\0';

  currentIndex = parsed.firstNameSize + parsed.firstNameIndex + 1;
  
  return (parsed.isLastName?atoi(&configStr[parsed.levelIndex]):-1);
}
