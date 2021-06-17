#ifndef CPPCHATCLIENT_VIEW_VIEW_H_
#define CPPCHATCLIENT_VIEW_VIEW_H_

#include <memory>
#include <string>

#include "../../include/cpp-chat-client/thread.h"
#include "../controller/observer.h"
#include "../model/friend-functionality/friend-node.h"

namespace chat_client_view {

class View : public thread_wrapper::Thread {
 public:
  virtual void Menu() = 0;
  virtual std::string GetInputUuidToAdd() = 0;
  virtual void AddFriendToFriendList(
      std::shared_ptr<chat_client_model_friend_functionality::FriendNode>) = 0;
  virtual void AddObserverAddFriendButton(
      chat_client_controller::Observer &controller) = 0;
};
}  // namespace chat_client_view

#endif