#include <memory>
#include <string>

#include "client-controller.h"

#include "../model/client-model.h"
#include "../view/MainApplication.h"

using namespace controller;
using namespace model;

ClientController::ClientController() {
  model = std::make_shared<ClientModel>();
  view = MainApplication::create(model);
}

void ClientController::Body(int argc, char **argv) {
  model->Run();
  view->run(argc, argv); // enters main gui loop - blocks until closed
}