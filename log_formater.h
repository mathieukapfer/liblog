#ifndef LOG_FORMATER_H
#define LOG_FORMATER_H

#include <stdint.h>
#include <stdio.h>


/*
   translate table to string
   NOTE: return the same pointer as buf, but filled with tab value as string
*/
template <typename T>
char * log_table2str(T tab[], int tabSize, char *buf, int bufSize) {
  int pos = 0;
  pos += snprintf(buf + pos, bufSize - pos, "{");
  for (int i=0; i < tabSize; i++) {
    pos += snprintf(buf + pos, bufSize - pos, "%d, ", tab[i]);
  }
  pos += snprintf(buf + pos, bufSize - pos, "}");
  return buf;
}

template char * log_table2str(uint8_t tab[], int tabSize, char *buf, int bufSize);
template char * log_table2str(uint16_t tab[], int tabSize, char *buf, int bufSize);
template char * log_table2str(uint32_t tab[], int tabSize, char *buf, int bufSize);
template char * log_table2str(uint64_t tab[], int tabSize, char *buf, int bufSize);

/* macro to use the formater */
#define LOG_TABLE_TO_STR(tab, size)                  \
  log_table2str(tab, size, logBuf, logBufSize)

#endif /* LOG_FORMATER_H */
