#ifndef CPPCHATCLIENT_THREAD_H_
#define CPPCHATCLIENT_THREAD_H_

#include <pthread.h>

namespace thread_wrapper {
class Thread {
 private:
  pthread_t _thread;

  static void *InternalThreadEntryFunc(void *This) {
    ((Thread *)This)->InternalThreadEntry();
    return NULL;
  }

 public:
  Thread() {}
  virtual ~Thread() {}

  int StartInternalThread() {
    return pthread_create(&_thread, NULL, InternalThreadEntryFunc, this);
  }

  void WaitForInternalThreadToExit() { (void)pthread_join(_thread, NULL); }

 protected:
  virtual void InternalThreadEntry() = 0;
};
}  // namespace thread_wrapper

#endif