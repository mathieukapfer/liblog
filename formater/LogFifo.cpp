#include "LogFifo.h"
#include <string.h>

#define MIN(a, b) (a < b ? a: b)

bool LogFifo::isEmpty() {
  bool ret = false;
  if(_mutex.Take()) {
    ret = (_logSlots[_slotPop].state <= BUZY);
    _mutex.Give();
  }
  return ret;
}

bool LogFifo::isFull() {
  bool ret = true;
  if (_mutex.Take()) {
    ret = ((_slotPush + 1) % nbslot == _slotPop) && (_logSlots[_slotPop].state > FREE);
    _mutex.Give();
  }
  return ret;
}

bool LogFifo::push(LogMsg  msg) {
  bool ret = true;
  bool goAhead = false;

  if(_mutex.Take()) {
    if (!isFull()) {
      // take next slot
      _slotPush = (_slotPush + 1) % nbslot;
      // continue
      goAhead = true;
    }
    _mutex.Give();
  }

  // update slot
  if (goAhead) {
    LogSlot *slot = &_logSlots[_slotPush];
    // change state
    slot->state = BUZY;
    // compute len if needed
    ///slot->len = msg.len?msg.len:strnlen(msg.buf, logMsgSizeMax);
    slot->len = msg.len?msg.len:strlen(msg.buf);
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
  return push(logMsg);
}

char *LogFifo::front() {
  char * ret = "\0";
  if (!isEmpty() /*_slot->state == FULL*/) {
    ret = _logSlots[_slotPop].buf;
  }
  return ret;
}

char *LogFifo::back() {
  char * ret = "\0";
  if (!isEmpty() /*_slot->state == FULL*/) {
    ret = _logSlots[_slotPush].buf;
  }
  return ret;
}


void LogFifo::front(LogMsg &msg) {
  if (!isEmpty() /*_slot->state == FULL*/) {
    LogSlot *_slot = &_logSlots[_slotPop];
    msg.len = _slot->len;
    msg.buf = _slot->buf;
  } else {
    msg.len = 0;
    msg.buf = "\0";
  }
}

void LogFifo::back(LogMsg &msg) {
  if (!isEmpty() /*_slot->state == FULL*/) {
    LogSlot *slot = &_logSlots[_slotPush];
    msg.len = slot->len;
    msg.buf = slot->buf;
  } else {
    msg.len = 0;
    msg.buf = "\0";
  }
}

void LogFifo::pop() {
  LogSlot *slot;

  if(_mutex.Take()) {
    slot = &_logSlots[_slotPop];
    if (slot->state == FULL) {
      // update state
      slot->state = FREE;
      // update index
      _slotPop = (_slotPop + 1) % nbslot;
    }
  _mutex.Give();
  }
}
