#include "send-message-observer.h"

#include <iostream>
#include <string>

using namespace controller_observers;
using namespace model;
using namespace std;

SendMessageObserver::SendMessageObserver(shared_ptr<ClientModel> model,
                                         Glib::RefPtr<MainApplication> view) {
  this->model = model;
  this->view = view;

  view->AddObserverSendButton(*this);
}

void SendMessageObserver::Execute() {
  string message = view->GetMessageBoxText();

  // model->SendMessage(message, );
}