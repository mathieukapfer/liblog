#include "log.h"
#include "MyClass2.h"

// register section 'MyClass2' as sub section of 'Main'
LOG_REGISTER("Main","MyClass2")

MyClass2::MyClass2() {
  LOG_NOTICE();
}

void MyClass2::aMethode() {
  // register
  LOG_REGISTER("Main","MyClass2","aMethode");

  {
    // register
    LOG_REGISTER("Main","MyClass2","aMethode","block");
    LOG_INFO("inside block")
  }

  // log something
  LOG_INFO("OK!");
}
