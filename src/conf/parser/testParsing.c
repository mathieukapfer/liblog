#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_TREAT_CHAR_STAR_AS_STRING
#include "doctest.h"

#include "parseConfString.h"
#include <string.h>

#include "log_for_logger.h"

ENABLE_LOG(INFO)

#define _CHECK_STRING(str, ref) (strncmp(str, ref, strlen(ref)) == 0)

TEST_SUITE("Check paring") {

  TEST_CASE("getFirstNameStr_") {

    char buf[100];
    const char *configureString = "name1.toto.zozo.momo:1";
    int current_index = 0;
    int ret = -1;
    
    do {
      ret = getFirstNameStr_(configureString, buf, current_index);
      LOG_INFO("%s:%d", buf, ret);
    } while (ret < 0 );
      
  }
  TEST_CASE("simple case") {

    int strIndex = 0;

    //                             0123456789012345
    const char *configureString = "name1.bigname2:1";
    char buf[100];
    ConfigStringParsed parsed;

    getFirstName(configureString, strIndex, parsed);

    LOG_INFO("%s %s %d %d %d",
             &configureString[parsed.firstNameIndex], &configureString[strIndex],
             parsed.firstNameSize, parsed.isLastName, strIndex);

    getFirstNameStr(configureString, buf);
    CHECK(buf == "name1");

    CHECK(_CHECK_STRING(&configureString[parsed.firstNameIndex], "name1"));
    CHECK(parsed.firstNameSize == 5);
    CHECK(parsed.isLastName == false);

    strIndex = parsed.firstNameSize + parsed.firstNameIndex + 1;
    getFirstName(configureString, strIndex, parsed);

    LOG_INFO("%s %s %d %d %d",
             &configureString[parsed.firstNameIndex], &configureString[strIndex],
             parsed.firstNameSize, parsed.isLastName, strIndex);

    CHECK(_CHECK_STRING(&configureString[parsed.firstNameIndex], "bigname2"));
    CHECK(parsed.firstNameSize == 8);
    CHECK(parsed.levelIndex == 15);
    CHECK(parsed.isLastName == true);
    strIndex = parsed.firstNameSize + parsed.firstNameIndex + 1;

  }
  TEST_CASE("simple case 2") {

    int strIndex = 0;

    //                             0123456789012345
    const char *configureString = "  name1.bigname2:1";
    ConfigStringParsed parsed;

    getFirstName(configureString, strIndex, parsed);

    LOG_INFO("%s %s %d %d %d",
             &configureString[parsed.firstNameIndex], &configureString[strIndex],
             parsed.firstNameSize, parsed.isLastName, strIndex);

    CHECK(_CHECK_STRING(&configureString[parsed.firstNameIndex], "name1"));
    CHECK(parsed.firstNameSize == 5);
    CHECK(parsed.isLastName == false);
    strIndex = parsed.firstNameSize + parsed.firstNameIndex + 1;

    getFirstName(configureString, strIndex, parsed);

    LOG_INFO("%s %s %d %d %d",
             &configureString[parsed.firstNameIndex], &configureString[strIndex],
             parsed.firstNameSize, parsed.isLastName, strIndex);

    CHECK(_CHECK_STRING(&configureString[parsed.firstNameIndex], "bigname2"));
    CHECK(parsed.firstNameSize == 8);
    CHECK(parsed.levelIndex == 17);
    CHECK(parsed.isLastName == true);
    strIndex = parsed.firstNameSize + parsed.firstNameIndex + 1;

  }
}
