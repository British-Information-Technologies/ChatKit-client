#include "deletefriend-observer.h"

#include <iostream>
#include <string>

#include "../view/view.h"

using namespace chat_client_view;
using namespace chat_client_controller;
using namespace chat_client_model;
using namespace std;

DeleteFriendObserver::DeleteFriendObserver(shared_ptr<ClientModel> model,
                                           shared_ptr<View> view) {
  this->model = model;
  this->view = view;

  view->AddObserverDeleteFriendButton(*this);
}

void DeleteFriendObserver::Execute() {
  string uuid = view->GetInputUuidToDelete();

  if (model->DeleteFriend(uuid)) {
    view->RemoveFriendFromFriendList(uuid);
    return;
  }

  cout << "already deleted" << endl;
}