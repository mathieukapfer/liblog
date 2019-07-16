#ifndef LOG_FIFO_I_H
#define LOG_FIFO_I_H

class LogFifoI {

 public:

  struct LogMsg {
    uint16_t len;
    char *buf;
  };

  // api with struct
  virtual bool push(LogMsg msg) = 0;
  virtual void front(LogMsg &msg) = 0;
  virtual void back(LogMsg &msg) = 0;

  // api with char *
  virtual bool push(char* msg) = 0;
  virtual char *front() = 0;
  virtual char *back() = 0;

  // pop last log
  virtual void pop() = 0;

  // fifo state
  virtual bool isEmpty() = 0;
  virtual bool isFull() = 0;

};


#endif /* LOG_FIFO_I_H */
