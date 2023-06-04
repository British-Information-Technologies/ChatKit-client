#include <memory>
#include <string>

#include "client-controller.h"

#include "../model/client-model.h"
#include "../view/MainApplication.h"

#include "observers/addfriend-observer.h"
#include "observers/deletefriend-observer.h"
#include "observers/send-message-observer.h"

#include "view-factory.h"

using namespace controller;
using namespace controller_observers;
using namespace model;

ClientController::ClientController(int argc, char **argv) {
  model = std::make_shared<ClientModel>();
}

void ClientController::Body() {
  model->Run();
}