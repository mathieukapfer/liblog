#include "log_utils.h"

const char * basename_const(const char * filename) {
  char * ret = 0;
  int index = 0;
  int slash = 0;

  while (filename[index] != '\0') {
    if(filename[index] == '/') {
      slash = index;
    }
    index++;
  }
  return &filename[slash+1];
}
