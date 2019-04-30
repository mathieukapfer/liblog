#include "log.h"
#include "MyClass3.h"

// register section 'MyClass3' as sub section of 'Main'
LOG_REGISTER("Main","MyClass3")

MyClass3::MyClass3() {
  LOG_INFO();
}

void MyClass3::aMethode() {
  // register
  LOG_REGISTER("Main","MyClass3","aMethode");

  // log something
  LOG_INFO("OK!");
}
