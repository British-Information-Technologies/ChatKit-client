#ifndef CPPCHATCLIENT_CONTROLLER_CLIENTCONTROLLER_H_
#define CPPCHATCLIENT_CONTROLLER_CLIENTCONTROLLER_H_

#include "../model/client-model.h"
#include "../view/view.h"
#include "observer.h"

namespace chat_client_controller {
class ClientController : public Observer {
 private:
  chat_client_model::ClientModel model;
  std::unique_ptr<chat_client_view::View> view;

 public:
  ClientController(int, char **);

  void AddFriend();
};
}  // namespace chat_client_controller

#endif