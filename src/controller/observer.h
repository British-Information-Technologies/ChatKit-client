#ifndef CPPCHATCLIENT_CONTROLLER_OBSERVER_H_
#define CPPCHATCLIENT_CONTROLLER_OBSERVER_H_

#include <memory>

namespace chat_client_view {
class View;
}

namespace chat_client_controller {
class Observer {
 protected:
  std::shared_ptr<chat_client_view::View> view;

 public:
  virtual void Execute() = 0;
};
}  // namespace chat_client_controller

#endif