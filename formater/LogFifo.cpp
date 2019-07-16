#include "LogFifo.h"
#include <string.h>

#define MIN(a,b) (a < b ? a: b)

bool LogFifo::isEmpty() {
  return (_logSlots[_slotPop].state <= BUZY);
}

bool LogFifo::isFull() {
  return ((_slotPush + 1) % nbslot == _slotPop) && (_logSlots[_slotPop].state > FREE);
}

bool LogFifo::push(LogMsg  msg) {
  bool ret = true;
  bool goAhead = false;

  // MUTEX TAKE
  if (!isFull()) {
    // take next slot
    _slotPush = (_slotPush + 1) % nbslot;
    // continue
    goAhead = true;
  }
  // MUTEX RELEASE

  // update slot
  if (goAhead) {
    LogSlot *slot = &_logSlots[_slotPush];
    // change state
    slot->state = BUZY;
    // compute len if needed
    slot->len = msg.len?msg.len:strnlen(msg.buf, logMsgSizeMax);
    // do the copy
    strncpy(slot->buf, msg.buf, logMsgSizeMax);
    // finalize state
    slot->state = FULL;
  } else {
    ret = false;
  }

  return ret;
}

bool LogFifo::push(char* msg) {
  LogMsg logMsg;
  logMsg.buf = msg;
  logMsg.len = 0;
  push(logMsg);
}

char *LogFifo::front() {
  char * ret = "\0";
  LogSlot *_slot = &_logSlots[_slotPop];
  if (!isEmpty() /*_slot->state == FULL*/) {
    ret = _logSlots[_slotPop].buf;
  }
  return ret;
}

char *LogFifo::back() {
  char * ret = "\0";
  LogSlot *_slot = &_logSlots[_slotPush];
  if (!isEmpty() /*_slot->state == FULL*/) {
    ret = _logSlots[_slotPush].buf;
  }
  return ret;
}


void LogFifo::front(LogMsg &msg) {
  LogSlot *_slot = &_logSlots[_slotPop];
  if (!isEmpty() /*_slot->state == FULL*/) {
    msg.len = _slot->len;
    msg.buf = _slot->buf;
  } else {
    msg.len = 0;
    msg.buf = "\0";
  }
}

void LogFifo::back(LogMsg &msg) {
  LogSlot *_slot = &_logSlots[_slotPush];
  if (!isEmpty() /*_slot->state == FULL*/) {
    msg.len = _slot->len;
    msg.buf = _slot->buf;
  } else {
    msg.len = 0;
    msg.buf = "\0";
  }
}

void LogFifo::pop() {
  // MUTEX TAKE
  LogSlot *_slot = &_logSlots[_slotPop];
  // release slot
  if (_slot->state == FULL) {
    _logSlots[_slotPop].state = FREE;
    // update index
    _slotPop = (_slotPop + 1) % nbslot;
  }
  // MUTEX RELEASE
}
