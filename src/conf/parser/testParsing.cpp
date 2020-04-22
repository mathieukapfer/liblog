#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_TREAT_CHAR_STAR_AS_STRING
#include "doctest.h"

#include "LogSpecParser.h"
#include "log_level.h"
#include <string.h>

#define GLOBAL_LOG_ENABLE
#include "log_for_logger.h"

ENABLE_LOG(INFO)

#define STRING_EQUAL(str, ref) (strncmp(str, ref, strlen(ref)) == 0)
#define PARSE_ONCE {char * p; parser.getFirstCatStr(&p);}

TEST_SUITE("Check parsing") {

  TEST_CASE("test isStartingWithRoot()") {
    {LogSpecParser parser("foo.bar");    CHECK(parser.isStartingWithRoot() ==  false);}
    {LogSpecParser parser("  foo.bar");    CHECK(parser.isStartingWithRoot() ==  false);}
    {LogSpecParser parser("GLOBAL.foo.bar");  CHECK(parser.isStartingWithRoot() ==  true);}
    {LogSpecParser parser("  GLOBAL.foo.bar");  CHECK(parser.isStartingWithRoot() ==  true);}
  }
  
  TEST_CASE("parse level") {
    // as int
    {LogSpecParser parser("foo.bar:0"); PARSE_ONCE; CHECK( parser.getLevel() == 0);}
    {LogSpecParser parser("foo.bar:1"); PARSE_ONCE; CHECK( parser.getLevel() == 1);}
    {LogSpecParser parser("foo.bar:2"); PARSE_ONCE; CHECK( parser.getLevel() == 2);}
    {LogSpecParser parser("foo.bar:3"); PARSE_ONCE; CHECK( parser.getLevel() == 3);}
    {LogSpecParser parser("foo.bar:100"); PARSE_ONCE; CHECK( parser.getLevel() == 100);}

    // as string
    {LogSpecParser parser("foo.bar:NONE"); PARSE_ONCE; CHECK( parser.getLevel() == LP_NONE);}
    {LogSpecParser parser("  	foo.bar: NONE"); PARSE_ONCE; CHECK( parser.getLevel() == LP_NONE);}
    {LogSpecParser parser("  	foo.bar: NONEfoofoofoo"); PARSE_ONCE; CHECK( parser.getLevel() == LP_NONE);}

    {LogSpecParser parser("foo.bar:INFO"); PARSE_ONCE; CHECK( parser.getLevel() == LP_INFO);}
    {LogSpecParser parser("  	foo.bar: INFO"); PARSE_ONCE; CHECK( parser.getLevel() == LP_INFO);}
    {LogSpecParser parser("  	foo.bar: INFOfoofoofoo"); PARSE_ONCE; CHECK( parser.getLevel() == LP_INFO);}
}

  TEST_CASE("test getNextCatStr step ") {

    #define STRING1 "name"
    #define STRING2 "subname"
    #define STRING3 "subsubname"
    #define STRING_LEVEL "9"
    
    LogSpecParser parser("    " STRING1 "." STRING2 "." STRING3 ":" STRING_LEVEL);
    char *cat;

    parser.getNextCatStr(&cat);
    CHECK(STRING_EQUAL(cat, STRING1));

    parser.getNextCatStr(&cat);
    CHECK(STRING_EQUAL(cat, STRING2));

    parser.getNextCatStr(&cat);
    CHECK(STRING_EQUAL(cat, STRING3));

    CHECK(parser.getLevel() == 9);
}
      
  TEST_CASE("test getNextCatStr loop") {

    LogSpecParser parser("    name1.toto.zozo.momo:9");
    char *cat;
    bool loop=true;

    while (loop) {
      loop = parser.getNextCatStr(&cat) == false;
      LOG_INFO("%s:%d (last:%d)", cat, parser.getLevel());
    } 
  }

  TEST_CASE("test overfow") {

    LogSpecParser parser(
      "123456789_123456789_123456789_123456789_123456789_123456789_123456789._123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789:9");
    
    char *cat;
    bool loop=true;

    while (loop) {
      loop = parser.getNextCatStr(&cat) == false;
      LOG_INFO("%s:%d (last:%d)", cat, parser.getLevel());
    } 

  }
}







