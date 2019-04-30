#include "log.h"
#include "MyClass.h"

LOG_REGISTER("Main","MyClass1")

MyClass::MyClass() {
  LOG_INFO();
}
