#ifndef VIEW_H
#define VIEW_H

#include "../../include/cpp-chat-client/Thread.h"

using namespace thread_wrapper;

namespace chat_client_view {
    class View: public Thread {
        public:
            virtual void menu() = 0;
    };
}

#endif