
// quick test formater

// to run it, just type:
//
//     make test_formater && ./test_formater
//

#include "../log_formater.h"

/*
 * embedded unit test
 */

#define logBufSize 255

int main(int argc, char *argv[]) {

  char buf[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
  char logBuf[logBufSize];

  // default format and start at index 0
  printf("%s\n", LOG_TABLE_TO_STR(buf, 4, 0));
  printf("%s\n", LOG_TABLE_TO_STR((uint16_t * )buf, 2, 0));
  printf("%s\n", LOG_TABLE_TO_STR((uint32_t * )buf, 1, 0));

  // use formater
  printf("%s\n", LOG_TABLE_TO_STR_(buf, 4, 0, "0x%x, "));
  printf("%s\n", LOG_TABLE_TO_STR_((uint16_t * )buf, 2, 0, "0x%x, "));
  printf("%s\n", LOG_TABLE_TO_STR_((uint32_t * )buf, 1, 0, "0x%x, "));

  // start with 1
  printf("%s\n", LOG_TABLE_TO_STR_(buf, 4, 1, "0x%x, "));
  printf("%s\n", LOG_TABLE_TO_STR_((uint16_t * )buf, 2, 1, "0x%x, "));
  printf("%s\n", LOG_TABLE_TO_STR_((uint32_t * )buf, 1, 1, "0x%x, "));

  return 0;
}
