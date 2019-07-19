#include "LogFifo.h"
#include <stdio.h>

#define DUMP(cmd, ...)                                                  \
  {                                                                     \
    char _cmd[10];                                                      \
    snprintf(_cmd, 10, cmd, ##__VA_ARGS__ ) ;                           \
    printf("%-10s, front:%-20s back:%-20s, empty:%d, full:%d\n",        \
           _cmd, fifo.front(), fifo.back(), fifo.isEmpty(), fifo.isFull() ); \
  }


int main(int argc, char *argv[]) {

  LogMutexI dummyMutex;
  LogFifo fifo(dummyMutex);

  // normal usage
  DUMP("init");
  fifo.push("this is a log 1");
  DUMP("push");
  fifo.push("this is a log 2222");
  DUMP("push");
  fifo.push("this is a log 3333333");
  DUMP("push");
  fifo.push("this is a log 4444444444");
  DUMP("nothing");
  DUMP("nothing");
  DUMP("nothing");
  fifo.pop();
  DUMP("pop");
  fifo.pop();
  DUMP("pop");
  fifo.pop();
  DUMP("pop");
  fifo.pop();

  // too many push
  for (int i=0; i < 40; i++) {
    char buf[100];
    snprintf(buf, 100, "too many push %d", i);
    fifo.push(buf);
    DUMP("push %d", i);
  }

  // too many pop
  for (int i=0; i < 50; i++) {
    char buf[100];
    fifo.pop();
    DUMP("pop %d", i);
  }

  return 0;
}
