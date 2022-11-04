#include "log.h"
#include "log_conf.h"
#include <unistd.h>

// File section name
LOG_REGISTER("File");

void aFunction() {  LOG_ENTER(); }

void anotherFunction() {
  LOG_ENTER();

  // Function section name
  LOG_REGISTER("File","aFunc");
  LOG_INFO("Nested section");
}

int main(int argc, char *argv[]) {
  // Function section name
  LOG_REGISTER("File","Main");

  aFunction();
  anotherFunction();

  int i = 42;
  sleep(1);
  LOG_DEBUG("Hello from main %d", i);

  // Display the log configuration
  LOG_DISLAY_TREE();
}