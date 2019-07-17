#ifndef LOGMUTEXI_H
#define LOGMUTEXI_H

class LogMutexI {
 public:
  // do nothing by default
  virtual bool Take() {return true;};
  virtual void Give() {};
};


#endif /* LOGMUTEXI_H */
