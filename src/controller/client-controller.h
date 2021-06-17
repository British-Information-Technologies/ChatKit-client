#ifndef CPPCHATCLIENT_CONTROLLER_CLIENTCONTROLLER_H_
#define CPPCHATCLIENT_CONTROLLER_CLIENTCONTROLLER_H_

#include "../model/client-model.h"
#include "../view/view.h"
#include "observer.h"

using namespace chat_client_view;
using namespace chat_client_model;

namespace chat_client_controller {
class ClientController : public Observer {
 private:
  ClientModel model;
  unique_ptr<View> view;

 public:
  ClientController(int, char **);

  void AddFriend();
};
}  // namespace chat_client_controller

#endif