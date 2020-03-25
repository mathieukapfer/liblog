#include "log.h"
#include "MyClass2.h"

// register section 'MyClass2' as sub section of 'Main'
LOG_REGISTER("Main","MyClass2")

MyClass2::MyClass2() {
  LOG_NOTICE();
}

void MyClass2::aMethode() {
  // register
  LOG_REGISTER("MyClass2","aMethode2");

  {
    // register
    LOG_REGISTER("aMethode2","block2");
    LOG_INFO("inside block")
  }

  // log something
  LOG_INFO("OK!");
}
