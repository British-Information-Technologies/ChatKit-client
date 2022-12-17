#ifndef CONTROLLER_CLIENT_CONTROLLER_H_
#define CONTROLLER_CLIENT_CONTROLLER_H_

#include "cpp-chat-client/model/client-model.h"
#include "cpp-chat-client/view/MainApplication.h"

namespace controller {
class ClientController {
 private:
  std::shared_ptr<model::ClientModel> model;
  Glib::RefPtr<MainApplication> view;

 public:
  ClientController(int, char **);

  void Body();
};
}  // namespace controller

#endif