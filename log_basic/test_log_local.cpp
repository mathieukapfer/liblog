#include "log.h"

int main(int argc, char *argv[])
{

  LOG_ENTER();
  LOG_ENTER("with param");
  LOG_DEBUG("hello");
  LOG_DEBUG("hello %d", 999);

  return 0;
}
