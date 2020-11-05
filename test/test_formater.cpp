
// quick test formater

// to run it, just type:
//
//     make test_formater && ./test_formater
//

#include "log_formater.h"

/*
 * embedded unit test
 */

#define logBufSize 255

int main(int argc, char *argv[]) {

  char buf[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
  char logBuf[logBufSize];

  printf("\n default format and start at index 0\n");
  printf("%s\n", LOG_TABLE_TO_STR(buf, 8, 0));
  printf("%s\n", LOG_TABLE_TO_STR((uint16_t * )buf, 4, 0));
  printf("%s\n", LOG_TABLE_TO_STR((uint32_t * )buf, 2, 0));
  printf("%s\n", LOG_TABLE_TO_STR((uint64_t * )buf, 1, 0));

  printf("\n formater %%d\n");
  printf("%s\n", LOG_TABLE_TO_STR_(buf, 8, 0, "%d, "));
  printf("%s\n", LOG_TABLE_TO_STR_((uint16_t * )buf, 4, 0, "%d, "));
  printf("%s\n", LOG_TABLE_TO_STR_((uint32_t * )buf, 2, 0, "%ld, "));
  printf("%s\n", LOG_TABLE_TO_STR_((uint64_t * )buf, 1, 0, "%lld, "));

  printf("\n formater %%x\n");
  printf("%s\n", LOG_TABLE_TO_STR_(buf, 8, 0, "0x%x, "));
  printf("%s\n", LOG_TABLE_TO_STR_((uint16_t * )buf, 4, 0, "0x%x, "));
  printf("%s\n", LOG_TABLE_TO_STR_((uint32_t * )buf, 2, 0, "0x%lx, "));
  printf("%s\n", LOG_TABLE_TO_STR_((uint64_t * )buf, 1, 0, "0x%llx, "));

  printf("\n start with 4\n");
  printf("%s\n", LOG_TABLE_TO_STR_(buf, 8, 4, "0x%x, "));
  printf("%s\n", LOG_TABLE_TO_STR_((uint16_t * )buf, 4, 4, "0x%x, "));
  printf("%s\n", LOG_TABLE_TO_STR_((uint32_t * )buf, 2, 4, "0x%x, "));

  return 0;
}
