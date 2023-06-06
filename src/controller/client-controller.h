#ifndef CONTROLLER_CLIENT_CONTROLLER_H_
#define CONTROLLER_CLIENT_CONTROLLER_H_

#include <gtkmm-4.0/gtkmm.h>

#include "../model/client-model.h"
#include "../view/MainApplication.h"

namespace controller {
class ClientController {
 private:
  std::shared_ptr<model::ClientModel> model;
  Glib::RefPtr<MainApplication> view;

 public:
  ClientController();

  void Body(int argc, char **argv);
};
}  // namespace controller

#endif