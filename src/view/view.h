#ifndef CPPCHATCLIENT_VIEW_VIEW_H_
#define CPPCHATCLIENT_VIEW_VIEW_H_

#include "../../include/cpp-chat-client/thread.h"

using namespace thread_wrapper;

namespace chat_client_view {
class View : public Thread {
 public:
  virtual void Menu() = 0;
};
}  // namespace chat_client_view

#endif