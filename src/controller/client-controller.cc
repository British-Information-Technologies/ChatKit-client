#include "client-controller.h"

#include <functional>
#include <iostream>
#include <string>

#include "view-factory.h"

using namespace chat_client_controller;
using namespace std::placeholders;
using namespace std;

ClientController::ClientController(int argc, char **argv) {
  ViewFactory factory;
  view = factory.CreateView(argc, argv);

  view->StartInternalThread();

  view->AddObserverAddFriendButton(*this);

  view->WaitForInternalThreadToExit();
}

void ClientController::AddFriend() {
  string uuid = view->GetInputUuidToAdd();

  if (model.AddFriend(uuid)) {
    shared_ptr<FriendNode> friend_node = model.GetFriend(uuid);
    view->AddFriendToFriendList(friend_node);
    return;
  }

  cout << "already exists" << endl;
}