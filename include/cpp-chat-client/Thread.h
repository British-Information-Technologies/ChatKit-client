#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>

namespace thread_wrapper {
    class Thread {
        private:
            pthread_t _thread;

            static void * internalThreadEntryFunc(void *This) {
                ((Thread *) This)->internalThreadEntry();
                return NULL;
            }

        public:
            Thread() {}
            virtual ~Thread() {}

            int startInternalThread() {
                return pthread_create(&_thread, NULL, internalThreadEntryFunc, this);
            }

            void waitForInternalThreadToExit() {
                (void) pthread_join(_thread, NULL);
            }

        protected:
            virtual void internalThreadEntry() = 0;
    };
}

#endif