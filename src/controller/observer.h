#ifndef CPPCHATCLIENT_CONTROLLER_OBSERVER_H_
#define CPPCHATCLIENT_CONTROLLER_OBSERVER_H_

namespace chat_client_controller {
class Observer {
 public:
  virtual void AddFriend() = 0;
};
}  // namespace chat_client_controller

#endif