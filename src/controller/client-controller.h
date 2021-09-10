#ifndef CONTROLLER_CLIENT_CONTROLLER_H_
#define CONTROLLER_CLIENT_CONTROLLER_H_

#include "../model/client-model.h"
#include "../view/MainApplication.h"

namespace controller {
class ClientController {
 private:
  std::shared_ptr<model::ClientModel> model;
  Glib::RefPtr<MainApplication> view;

 private:
  void *NetworkManager(void);

  static void *NetworkManagerHelper(void *context);

 public:
  ClientController(int, char **);

  void Body();
};
}  // namespace controller

#endif