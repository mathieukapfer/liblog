#include "log.h"
LOG_REGISTER("File"); //<-- Create a default category for the entire file

void aFunction() {LOG_ENTER();}

int main(int argc, char *argv[]) {
  int i = 123;
  aFunction();
  LOG_REGISTER("Main");               //<-- Create a category 'Main'
  LOG_DEBUG("Hello - in main %d", i); //<-- Log as DEBUG level
  {
    LOG_REGISTER("Main", "Section");    //<-- Create a sub category 'Section'
    LOG_INFO("Hello - inside section"); //<-- Log as INFO level
  }
}