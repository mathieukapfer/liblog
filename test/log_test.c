#include "log.h"
#include "MyClass.h"
#include "MyClass2.h"
#include "LogFile.h"

LOG_REGISTER("Main");

int main(int argc, char *argv[]) {

  MyClass myClass;
  MyClass2 myClass2;
  LOG_NOTICE("Hello - in main")
  {
    LOG_REGISTER("Main","BlockOfmain");
    LOG_INFO("hello - inside block");
  }

  myClass2.aMethode();

  LOG_INFO("end");

  LOG_DISLAY_TREE();

  LOG_CONFIGURE("Main.MyClass2:2");
  LOG_DISLAY_TREE();

  LOG_CONFIGURE("Main.MyClass1:TRACE");
  LOG_DISLAY_TREE();

  LOG_CONFIGURE("Main:3");
  LOG_DISLAY_TREE();

  LOG_CONFIGURE("GLOBAL:0");
  LOG_DISLAY_TREE();

  LOG_INFO("Hello - in main");
  {
  LOG_REGISTER("Main","BlockOfmain");
  LOG_INFO("hello - inside block");
  }

  LOG_CONFIGURE("GLOBAL        : INFO");
  LOG_DISLAY_TREE();

  LOG_INFO("Hello - in main");
  {
  LOG_REGISTER("Main","BlockOfmain");
  LOG_INFO("hello - inside block");
  }

  LOG_CONFIGURE("TOTO        : TITI");

  LogFile logFile;
  logFile.parseFile();

  return 0;
}
