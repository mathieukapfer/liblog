#include "log.h"
#include "MyClass.h"
#include "MyClass2.h"
#include "MyClass3.h"
#include "LogFile.h"

LOG_REGISTER("Main");

int main(int argc, char *argv[]) {

  static const char *msg = "!!!!!";

  LOG_EMERGENCY("ENTER");

  // test configuration before declaration
  LOG_CONFIGURE("GLOBAL:7");
  LOG_DISLAY_TREE();
  LOG_CONFIGURE("Main.MyClass2.aMethode:8");
  LOG_DISLAY_TREE();
  LOG_CONFIGURE("Main.MyClass2.aMethode.block:3");
  LOG_DISLAY_TREE();

  LogFile logFile;
  logFile.parseFile();

  MyClass myClass;
  MyClass2 myClass2;
  MyClass3 myClass3;

  LOG_NOTICE("Hello - in main: %s", msg);
  LOG_NOTICE("Hello - in main: %d", 999);

  myClass2.aMethode();
  LOG_CONFIGURE("Main.MyClass2.aMethode:2");

  LOG_DISLAY_TREE();

  return 0;
}
