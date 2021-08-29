#include "addfriend-observer.h"

#include <iostream>
#include <string>

using namespace chat_client_controller_observers;
using namespace chat_client_model;
using namespace std;

AddFriendObserver::AddFriendObserver(shared_ptr<ClientModel> model,
                                     Glib::RefPtr<MainApplication> view) {
  this->model = model;
  this->view = view;

  view->AddObserverAddFriendButton(*this);
}

void AddFriendObserver::Execute() {
  string uuid = view->GetInputUuidToAdd();

  if (model->AddFriend(uuid)) {
    shared_ptr<FriendNode> friend_node = model->GetFriend(uuid);
    view->AddFriendToFriendList(friend_node);
    return;
  }

  cout << "already exists" << endl;
}