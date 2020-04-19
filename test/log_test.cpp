#include <stdlib.h>
#include <stdio.h>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_TREAT_CHAR_STAR_AS_STRING
#include "doctest.h"

#include "log.h"
#include "log_conf.h"
#include "MyClass.h"
#include "MyClass2.h"
#include "MyClass3.h"
#include "LogConfFile.h"
#include "LogFacade.h"

#ifdef ENABLE_COPY_CONF_TO_MEM
// define a void buffer to receive the conf strings
char MEM_PTR[500];
//const char * LOG_CONF_MEM_PTR =  MEM_PTR;
#else
// define the conf strings into mem
const char cfg[] = {
  "# this is a comment \n"
  " # this is a comment with space before\n"
  " \t# this is a comment with space & tab before\n"
  "GLOBAL                   :EMERG(1)\n"
  "GLOBAL                   :EMERG\n"
  "GLOBAL                   :1\n"
  "Main                     :FATAL(2)\n"
  "Main.MyClass1            :CRIT(3)\n"
  "Main.MyClass2            :ERROR(4)\n"
  "Main.MyClass3            :WARN(5)\n"
};
// get the above filled buffer
const char * LOG_CONF_MEM_PTR = cfg;
#endif


#if 0
// ca marche pas :0(
#define CHECK_LEVEL__(agregat) {                                         \
    int tableLevelExpected[] = agregat;                                 \
    checkLevel(tableLevelExpected, sizeof(tableLevelExpected)/sizeof(int)); \
  }
#endif

#define CHECK_LEVEL(a, b, c, d, e) {                          \
    int tableLevelExpected[] = {a, b, c, d, e};               \
    int ret = checkLevel(tableLevelExpected, 5);              \
    CHECK(ret == true);                                       \
  }                                                           \

#define CHECK_LEVEL_(a, b, c, d, e, f) {                      \
  int tableLevelExpected[] = {a, b, c, d, e, f};              \
  int ret = checkLevel(tableLevelExpected, 6);                \
  CHECK(ret == true);                                         \
  }                                                           \

#define CHECK_LEVEL__(a, b, c, d, e, f, g, h) {                 \
    int tableLevelExpected[] = {a, b, c, d, e, f, g, h};          \
  int ret = checkLevel(tableLevelExpected, 8);                \
  CHECK(ret == true);                                         \
  }                                                           \

//#define VERBOSE

bool checkLevel(int* tableLevel, int tableSize) {
  bool ret;
  ret = LogFacade::inst().compareLevel(tableLevel, tableSize);
  if (ret == false)  {
    LogFacade::inst().printTable();
    //LOG_DISLAY_TREE();
  } else {
#ifdef VERBOSE
  LogFacade::inst().printTable();
  //LOG_DISLAY_TREE();
#endif
  }
  return ret;
}

//int main(int argc, char *argv[]) {
TEST_SUITE("Configure global") {

#ifdef ENABLE_FILE_SYSTEM
  TEST_CASE("by file") {

#ifdef ENABLE_COPY_CONF_TO_MEM
    // register the local buffer to receive the copy of conf
    LOG_REGISTER_MEM_CONF_ADDR(MEM_PTR);

    const char sep[] = "\n===========================================\n";
    printf("\n\nCONF COPY TO MEM:%s%s%s", sep, MEM_PTR, sep);
#endif

// test display tree
    LOG_DISLAY_TREE();

    // check default level
    CHECK_LEVEL(1, 2, 3, 4, 5);

  }
#else
  TEST_CASE("by mem") {

    // test display tree
    LOG_DISLAY_TREE();

    // check default level
    CHECK_LEVEL(1, 2, 3, 4, 5);
  }
#endif
}

TEST_SUITE("Configure by code ") {

  TEST_CASE("by code with int") {
    // test level configuration by int
    for (int level=0; level <= LP_TRACE; level++) {
      char confStr[100];
      sprintf(confStr, "GLOBAL:%d", level);
      LOG_CONFIGURE(confStr);
      CHECK_LEVEL(level, level, level, level, level);
    }
  }

  TEST_CASE("by code with string") {

  // test level configuration  by string
  LOG_CONFIGURE("GLOBAL:NONE");  CHECK_LEVEL(0, 0, 0, 0, 0) ;
  LOG_CONFIGURE("GLOBAL:EMERG"); CHECK_LEVEL(1, 1, 1, 1, 1) ;
  LOG_CONFIGURE("GLOBAL:FATAL"); CHECK_LEVEL(2, 2, 2, 2, 2) ;
  LOG_CONFIGURE("GLOBAL:CRIT");  CHECK_LEVEL(3, 3, 3, 3, 3) ;
  LOG_CONFIGURE("GLOBAL:ERROR"); CHECK_LEVEL(4, 4, 4, 4, 4) ;
  LOG_CONFIGURE("GLOBAL:WARN");  CHECK_LEVEL(5, 5, 5, 5, 5) ;
  LOG_CONFIGURE("GLOBAL:NOTIC"); CHECK_LEVEL(6, 6, 6, 6, 6) ;
  LOG_CONFIGURE("GLOBAL:INFO");  CHECK_LEVEL(7, 7, 7, 7, 7) ;
  LOG_CONFIGURE("GLOBAL:DEBUG"); CHECK_LEVEL(8, 8, 8, 8, 8) ;
  LOG_CONFIGURE("GLOBAL:TRACE"); CHECK_LEVEL(9, 9, 9, 9, 9) ;
  }

  TEST_CASE("check inheritge") {

  // test inheritage
  LOG_CONFIGURE("GLOBAL:NONE");
  LOG_CONFIGURE("GLOBAL                   :TRACE(9) ");  CHECK_LEVEL(9, 9, 9, 9, 9)
  LOG_CONFIGURE("GLOBAL:NONE");
  LOG_CONFIGURE("Main                     :TRACE(9) ");  CHECK_LEVEL(0, 9, 9, 9, 9)
  LOG_CONFIGURE("GLOBAL:NONE");
  LOG_CONFIGURE("Main.MyClass1            :TRACE(9) ");  CHECK_LEVEL(0, 0, 9, 0, 0)
  LOG_CONFIGURE("GLOBAL:NONE");
  LOG_CONFIGURE("Main.MyClass2            :TRACE(9) ");  CHECK_LEVEL(0, 0, 0, 9, 0)
  LOG_CONFIGURE("GLOBAL:NONE");
  LOG_CONFIGURE("Main.MyClass3            :TRACE(9) ");  CHECK_LEVEL(0, 0, 0, 0, 9)
  LOG_CONFIGURE("GLOBAL:NONE");
  LOG_CONFIGURE("Main.MyClass2.aMethode   :DEBUG(8) // cmt"); CHECK_LEVEL_(0, 0, 0, 0, 0, 8)
  LOG_CONFIGURE("GLOBAL:TRACE");
  }

  TEST_CASE("check configuration of node not yet declated") {
  // test configuration before declaration
  LOG_CONFIGURE("Main.MyClass2.aMethode:8");
  LOG_CONFIGURE("Main.MyClass2.aMethode.block:3");
  LOG_CONFIGURE("Main2:2");
  LOG_DISLAY_TREE();

  // check before declaration
  CHECK_LEVEL__(9, 9, 9, 9, 9, 8, 3, 2);

  // test reset of preallocated flag
  MyClass myClass;
  MyClass3 myClass3;
  MyClass2 myClass2;
  myClass2.aMethode();

  // check after declaration
  CHECK_LEVEL__(9, 9, 9, 9, 9, 8, 3, 2);

  // test again level inheritage
  LOG_CONFIGURE("Main.MyClass2:2");

  // check again inheritage
  CHECK_LEVEL__(9, 9, 9, 2, 9, 2, 2, 2);

  LOG_DISLAY_TREE();
  }
}

TEST_SUITE("Format") {

  TEST_CASE("check printf format") {
  static const char *msg = "!!!!!";
  const float myFloat = 1.1234;

  LOG_REGISTER("TestFormat");

  // test log with parameter
  LOG_ENTER("\ntest enter");
  LOG_NOTICE("Hello - in main: %s", msg);
  LOG_NOTICE("Hello - in main: %d", 999);
  LOG_NOTICE("Hello - in main: %s %d %f", msg, 999, myFloat);
  LOG_DEBUG("Hello - in main: %s %d %f", msg, 999, myFloat);
  LOG_EXIT("test exit");

  LOG_DISLAY_TREE();
  }

  TEST_CASE("test tab as sring formater") {
    LOG_REGISTER("TestFormat");

    uint16_t tab[] = { 1, 2, 3, 4, 5 };
    LOG_DEBUG("\ntab:%s", LOG_TABLE_TO_STR(tab,5,0));
  }
}
