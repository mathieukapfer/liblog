#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_TREAT_CHAR_STAR_AS_STRING
#include "doctest.h"

#include "parseConfString.h"
#include <string.h>

#include "log_for_logger.h"

ENABLE_LOG(INFO)

#define STRING_EQUAL(str, ref) (strncmp(str, ref, strlen(ref)) == 0)

TEST_SUITE("Check parsing") {

  TEST_CASE("isFirstName=RootName") {
    {
      ConfigurationStringParser parser("toto.titi");    
      CHECK(parser.isStartingWithRoot() ==  false);
    }
    {
     ConfigurationStringParser parser("GLOBAL.toto.titi");    
      CHECK(parser.isStartingWithRoot() ==  true);
    }
  }
  TEST_CASE("getNextCatStr strep ") {

    #define STRING1 "name"
    #define STRING2 "subname"
    #define STRING3 "subsubname"
    #define STRING_LEVEL "9"
    
    ConfigurationStringParser parser("    " STRING1 "." STRING2 "." STRING3 ":" STRING_LEVEL);
    char *cat;

    parser.getNextCatStr(&cat);
    CHECK(STRING_EQUAL(cat, STRING1));

    parser.getNextCatStr(&cat);
    CHECK(STRING_EQUAL(cat, STRING2));

    parser.getNextCatStr(&cat);
    CHECK(STRING_EQUAL(cat, STRING3));

    CHECK(parser.getLevel() == 9);
}
      
  TEST_CASE("getNextCatStr loop") {

    ConfigurationStringParser parser("    name1.toto.zozo.momo:9");
    char *cat;

    while (parser.getNextCatStr(&cat) == false) {
      LOG_INFO("%s:%d (last:%d)", cat, parser.getLevel());
    } 
      
  }
}







