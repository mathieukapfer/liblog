#include <stdlib.h>
#include <stdio.h>

#include "log.h"
#include "MyClass.h"
#include "MyClass2.h"
#include "MyClass3.h"
#include "LogFile.h"


#if 0
// ca marche pas :0(
#define CHECK_LEVEL_(agregat) {                                         \
    int tableLevelExpected[] = agregat;                                 \
    checkLevel(tableLevelExpected, sizeof(tableLevelExpected)/sizeof(int)); \
  }
#endif

#define CHECK_LEVEL(a, b, c, d, e) {            \
    int tableLevelExpected[] = {a, b, c, d, e}; \
    checkLevel(tableLevelExpected, 5);          \
  }                                             \

#define CHECK_LEVEL_(a, b, c, d, e, f) {           \
    int tableLevelExpected[] = {a, b, c, d, e, f};  \
    checkLevel(tableLevelExpected, 6);          \
  }                                             \

LOG_REGISTER("Main");

//#define VERBOSE

bool checkLevel(int* tableLevel, int tableSize) {
  bool ret;
  ret = LogNodeFactory::inst().compareLevel(tableLevel, tableSize);
  if (ret == false)  {
    printf("\nTEST ERROR: assert failed\n");
    LogNodeFactory::inst().printTable();
    exit(-1);
    //LOG_DISLAY_TREE();
  } else {
    printf("\nTEST OK\n");
#ifdef VERBOSE
  LogNodeFactory::inst().printTable();
  //LOG_DISLAY_TREE();
#endif
  }

}

int main(int argc, char *argv[]) {

  static const char *msg = "!!!!!";

  LOG_EMERGENCY("ENTER");

  // test default level
  LOG_DISLAY_TREE();

  // test level by int
  for (int level=0; level <= LP_TRACE; level++) {
    char confStr[100];
    sprintf(confStr, "GLOBAL:%d", level);
    LOG_CONFIGURE(confStr);
    CHECK_LEVEL(level, level, level, level, level);
  }

  // test level by string
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

  // test configuration before declaration
  LOG_CONFIGURE("Main.MyClass2.aMethode:8");
  LOG_CONFIGURE("Main.MyClass2.aMethode.block:3");
  LOG_DISLAY_TREE();

  // test reset of preallocated flag
  MyClass myClass;
  MyClass3 myClass3;
  MyClass2 myClass2;
  myClass2.aMethode();
  LOG_DISLAY_TREE();

  // test log with parameter
  LOG_NOTICE("Hello - in main: %s", msg);
  LOG_NOTICE("Hello - in main: %d", 999);
  LOG_NOTICE("Hello - in main: %s %d", msg, 999);

  // test again level conf
  LOG_CONFIGURE("Main.MyClass2.aMethode:2");

  LOG_DISLAY_TREE();

  return 0;
}
