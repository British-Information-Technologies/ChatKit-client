#include "deletefriend-observer.h"

#include <iostream>
#include <string>

using namespace controller_observers;
using namespace model;
using namespace std;

DeleteFriendObserver::DeleteFriendObserver(shared_ptr<ClientModel> model,
                                           Glib::RefPtr<MainApplication> view) {
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