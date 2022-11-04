#include "log.h"
#include "log_conf.h"
#include <unistd.h>

// File section name
LOG_REGISTER("File");

void aFunction() {  LOG_ENTER(); }

void anotherFunction() {
  // Function section name
  LOG_REGISTER("Main","aFunc");
  LOG_ENTER();
}

int main(int argc, char *argv[]) {
  // Function section name
  LOG_REGISTER("File","Main");

  aFunction();

  int i = 42;
  sleep(1);
  LOG_DEBUG("Hello from main %d", i);

  anotherFunction();

  // Display the log configuration
  LOG_DISLAY_TREE();
}