#ifndef CPPCHATCLIENT_CONTROLLER_OBSERVERS_SEND_MESSAGE_OBSERVER_H_
#define CPPCHATCLIENT_CONTROLLER_OBSERVERS_SEND_MESSAGE_OBSERVER_H_

#include "../../model/client-model.h"
#include "../../view/MainApplication.h"
#include "observer.h"

namespace chat_client_controller_observers {

class SendMessageObserver : public Observer {
 private:
  std::shared_ptr<chat_client_model::ClientModel> model;

 public:
  SendMessageObserver(std::shared_ptr<chat_client_model::ClientModel>,
                      Glib::RefPtr<MainApplication>);

  void Execute();
};

}  // namespace chat_client_controller_observers

#endif