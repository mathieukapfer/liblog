#ifndef LOG_FORMATER_H
#define LOG_FORMATER_H

#include <stdint.h>
#include <stdio.h>

/*
   translate table to string
   NOTE: return the same pointer as buf, but filled with tab value as string
*/
template <typename T>
char * log_table2str(T tab[], int nb, int start, char *buf, int bufSize, const char *format = "%Ld, ") {
  int pos = 0;
  pos += snprintf(buf + pos, bufSize - pos, "{ ");
  for (int i=start; i < nb + start; i++) {
    pos += snprintf(buf + pos, bufSize - pos, format, tab[i]);
  }
  pos += snprintf(buf + pos, bufSize - pos, " }");
  return buf;
}

template char * log_table2str(uint8_t tab[], int tabSize, int start, char *buf, int bufSize, const char *format = "%d, ");
template char * log_table2str(uint16_t tab[], int tabSize, int start, char *buf, int bufSize, const char *format = "%d, ");
template char * log_table2str(uint32_t tab[], int tabSize, int start, char *buf, int bufSize, const char *format = "%ld, ");
template char * log_table2str(uint64_t tab[], int tabSize, int start, char *buf, int bufSize, const char *format = "%lld, ");

template char * log_table2str(int8_t tab[], int tabSize, int start, char *buf, int bufSize, const char *format = "%d, ");
template char * log_table2str(int16_t tab[], int tabSize, int start, char *buf, int bufSize, const char *format = "%d, ");
template char * log_table2str(int32_t tab[], int tabSize, int start, char *buf, int bufSize, const char *format = "%ld, ");
template char * log_table2str(int64_t tab[], int tabSize, int start, char *buf, int bufSize, const char *format = "%lld, ");

/* macro to use the formater */
#define LOG_TABLE_TO_STR(tab, nb, start)              \
  log_table2str(tab, nb, start, logBuf, logBufSize)

#define LOG_TABLE_TO_STR_(tab, nb, start, format)            \
  log_table2str(tab, nb, start, logBuf, logBufSize, format)

#endif /* LOG_FORMATER_H */
