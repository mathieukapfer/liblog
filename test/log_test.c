#include "log.h"
#include "MyClass.h"
#include "MyClass2.h"
#include "MyClass3.h"
#include "LogFile.h"

#include <stdio.h>

LOG_REGISTER("Main");

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
    LOG_DISLAY_TREE();
  }

  // test level by string
  LOG_CONFIGURE("GLOBAL:NONE");  LOG_DISLAY_TREE();
  LOG_CONFIGURE("GLOBAL:EMERG"); LOG_DISLAY_TREE();
  LOG_CONFIGURE("GLOBAL:FATAL"); LOG_DISLAY_TREE();
  LOG_CONFIGURE("GLOBAL:CRIT");  LOG_DISLAY_TREE();
  LOG_CONFIGURE("GLOBAL:ERROR"); LOG_DISLAY_TREE();
  LOG_CONFIGURE("GLOBAL:WARN");  LOG_DISLAY_TREE();
  LOG_CONFIGURE("GLOBAL:NOTIC"); LOG_DISLAY_TREE();
  LOG_CONFIGURE("GLOBAL:INFO");  LOG_DISLAY_TREE();
  LOG_CONFIGURE("GLOBAL:DEBUG"); LOG_DISLAY_TREE();
  LOG_CONFIGURE("GLOBAL:TRACE"); LOG_DISLAY_TREE();

  // test inheritage
  LOG_DISLAY_TREE(); LOG_CONFIGURE("GLOBAL:NONE");
  LOG_CONFIGURE("GLOBAL                   :TRACE(9) ");
  LOG_DISLAY_TREE(); LOG_CONFIGURE("GLOBAL:NONE");
  LOG_CONFIGURE("Main                     :TRACE(9) ");
  LOG_DISLAY_TREE(); LOG_CONFIGURE("GLOBAL:NONE");
  LOG_CONFIGURE("Main.MyClass1            :TRACE(9) ");
  LOG_DISLAY_TREE(); LOG_CONFIGURE("GLOBAL:NONE");
  LOG_CONFIGURE("Main.MyClass2            :TRACE(9) ");
  LOG_DISLAY_TREE(); LOG_CONFIGURE("GLOBAL:NONE");
  LOG_CONFIGURE("Main.MyClass3            :TRACE(9) ");
  LOG_DISLAY_TREE(); LOG_CONFIGURE("GLOBAL:NONE");
  LOG_CONFIGURE("Main.MyClass2.aMethode   :DEBUG(8) // cmt");
  LOG_DISLAY_TREE(); LOG_CONFIGURE("GLOBAL:TRACE");

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
