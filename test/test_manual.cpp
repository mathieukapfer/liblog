#include "log.h"
#include "MyClass.h"
#include "MyClass2.h"
#include "MyClass3.h"
#include "LogConfFile.h"

int main(int argc, char *argv[]) {

  MyClass myClass;
  MyClass3 myClass3;
  MyClass2 myClass2;
  LOG_DISLAY_TREE();

  myClass2.aMethode(); 
  LOG_DISLAY_TREE();

  myClass.aMethode(); 
  LOG_DISLAY_TREE();

  return 0;
}

