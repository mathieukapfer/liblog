#ifndef LOG_TIMESTAMP_H
#define LOG_TIMESTAMP_H

#define NO_TIMESTAMP '\0'

#include <stdint.h>

// default formater
char * formatTimestamp(char * buf, int buf_size);

// register tick api - (targeted for freertos)
void registerTickCount(uint32_t (*xTaskGetTickCount)( void ));

#endif /* LOG_TIMESTAMP_H */
