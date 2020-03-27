// logger api
#include "log.h"

// set a name for all log in this file
LOG_REGISTER("Main");

int main(int argc, char *argv[])
{
  LOG_ENTER();
  LOG_ENTER("with param");
  LOG_DEBUG("hello");
  LOG_DEBUG("hello %d", 999);

  return 0;
}
