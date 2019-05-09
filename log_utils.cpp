#include "log_utils.h"

const char * basename_const(const char * filename) {
  char * ret = 0;
  int index = 0;
  int slash = -1; // keep this special value - see comment below

  while (filename[index] != '\0') {
    if(filename[index] == '/') {
      slash = index;
    }
    index++;
  }
  // note the special value -1 that became 0 if no slash is detected
  return &filename[slash+1];
}
