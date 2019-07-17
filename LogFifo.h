#ifndef LOG_FIFO_H
#define LOG_FIFO_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "LogFifoI.h"
#include "LogMutexI.h"

#define nbslot 32
#define logMsgSizeMax 256

class LogFifo: public LogFifoI {

 public:
  explicit LogFifo(LogMutexI &mutex):_mutex(mutex), _slotPush(-1), _slotPop(0) {
    memset(_logSlots, 0, sizeof(LogSlot) * nbslot);
  }

  virtual ~LogFifo() {
  };

  // api with struct
  bool push(LogMsg msg);
  void front(LogMsg &msg);
  void back(LogMsg &msg);

  // api with char *
  bool push(char* msg);
  char *front();
  char *back();

  // pop last log
  void pop();

  // fifo state
  bool isEmpty();
  bool isFull();

 private:

  enum LogSlotState {
    FREE = 0,
    BUZY,
    FULL,
  };

  struct LogSlot {
    LogSlotState state;
    int len;
    char buf[logMsgSizeMax];
  };

  LogMutexI &_mutex;
  LogSlot _logSlots[nbslot];
  int _slotPush;
  int _slotPop;
};


#endif /* LOG_FIFO_H */
