/**
 * @file   parseConfigurationString.c
 * @author Mathieu <mathieu@debian>
 * @date   Tue May  7 09:51:46 2019
 *
 * @brief  Stuff to parse configuration string
 *
 *
 */

#include <string.h>
#include "log_for_logger.h"
#include "parseConfigurationString.h"

ENABLE_LOG(INFO);

/**
 * Parse the configuration string to extract the first name
 *
 * @param configureString  the configuration string:
                           "category = 1",
                           "category.subcategory = 1"
                           "category.subcategory.anotherSubCategory = 1"
 * @param index            current position to parse into the configuration string
 * @param firstName        pointer to the first name
 * @param firstNameSize    size of first name
 * @param isLastName       true if the name is also the last
 */
void getFirstName(const char * configureString, int &index, ConfigStringParsed &parsed) {

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
  index = (sep - start) + 1 + index;

  LOG_INFO("%s %s %d %d %d",
           &configureString[ parsed.firstNameIndex], &configureString[index],
           parsed.firstNameSize, parsed.isLastName, index);

}
