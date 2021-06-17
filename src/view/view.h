#ifndef CPPCHATCLIENT_VIEW_VIEW_H_
#define CPPCHATCLIENT_VIEW_VIEW_H_

#include <gtk/gtk.h>

#include <functional>
#include <memory>
#include <string>

#include "../../include/cpp-chat-client/thread.h"
#include "../controller/observer.h"
#include "../model/friend-functionality/friend-node.h"

using namespace thread_wrapper;
using namespace chat_client_model_friend_functionality;
using namespace std;
using namespace chat_client_controller;

namespace chat_client_view {

class View : public Thread {
 public:
  virtual void Menu() = 0;
  virtual string GetInputUuidToAdd() = 0;
  virtual void AddFriendToFriendList(shared_ptr<FriendNode>) = 0;
  virtual void AddObserverAddFriendButton(Observer &controller) = 0;
};
}  // namespace chat_client_view

#endif