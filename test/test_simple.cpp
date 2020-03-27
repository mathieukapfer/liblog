#include "log.h"

int main(int argc, char *argv[]) {

  { LOG_REGISTER("Main"); };  LOG_DISLAY_TREE();
  { LOG_REGISTER("Main","module1"); };  LOG_DISLAY_TREE();
  { LOG_REGISTER("Main","module1","submodule1"); };  LOG_DISLAY_TREE();
  { LOG_REGISTER("Main","module2"); };  LOG_DISLAY_TREE();
  { LOG_REGISTER("Main","module2","submodule1"); };  LOG_DISLAY_TREE();

  return 0;
}

