#include "LogFifo.h"
#include <stdio.h>

int main(int argc, char *argv[]) {

  LogFifo fifo;

  // normal usage
  fifo.push("this is a log 1");
  printf("push:front:%s (back:%s)\n", fifo.front(), fifo.back());
  fifo.push("this is a log 2222");
  printf("push:front:%s (back:%s)\n", fifo.front(), fifo.back());
  fifo.push("this is a log 3333333");
  printf("push:front:%s (back:%s)\n", fifo.front(), fifo.back());
  fifo.push("this is a log 4444444444");
  printf("front-same:%s (back:%s)\n", fifo.front(), fifo.back());
  printf("front-same:%s (back:%s)\n", fifo.front(), fifo.back());
  printf("front-same:%s (back:%s)\n", fifo.front(), fifo.back());
  fifo.pop();
  printf("pop:front:%s (back:%s)\n", fifo.front(), fifo.back());
  fifo.pop();
  printf("pop:front:%s (back:%s)\n", fifo.front(), fifo.back());
  fifo.pop();
  printf("pop:front:%s (back:%s)\n", fifo.front(), fifo.back());
  fifo.pop();
  printf("pop:front:%s (back:%s)\n", fifo.front(), fifo.back());

  // too many push
  for (int i=0; i < 40; i++) {
    char buf[100];
    snprintf(buf, 100, "too many push %d", i);
    fifo.push(buf);
    printf("push[%d]:front:%s (back:%s)\n", i, fifo.front(), fifo.back());
  }

  // too many pop
  for (int i=0; i < 50; i++) {
    char buf[100];
    printf("pop[%d]:front:%s (back:%s)\n ", i, fifo.front(), fifo.back());
    fifo.pop();
  }

  return 0;
}
