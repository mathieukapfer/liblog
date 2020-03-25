#include "log.h"
#include "MyClass.h"

LOG_REGISTER("Main","MyClass1")

MyClass::MyClass() {
  LOG_INFO();
}

void MyClass::aMethode() {
  // register
  LOG_REGISTER("MyClass1","aMethode1");

  {
    // register
    LOG_REGISTER("aMethode1","block1");
    LOG_INFO("inside block")
  }

  // log something
  LOG_INFO("OK!");
}
