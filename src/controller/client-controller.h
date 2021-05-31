#ifndef CPPCHATCLIENT_CONTROLLER_CLIENTCONTROLLER_H_
#define CPPCHATCLIENT_CONTROLLER_CLIENTCONTROLLER_H_

#include "../view/view.h"

using namespace chat_client_view;

namespace chat_client_controller {
class ClientController {
 private:
  View* view;

 public:
  ClientController(int, char**);
};
}  // namespace chat_client_controller

#endif