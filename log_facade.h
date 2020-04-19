#ifndef LOG_FACADE_H
#define LOG_FACADE_H

/// create node 
void * getNode(const char* catName, int preAllocated, ...);

/// getter to log level of node
int getLogLevel(void *catv);

#endif /* LOG_FACADE_H */
