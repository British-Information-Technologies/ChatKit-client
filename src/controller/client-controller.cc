#include "client-controller.h"

#include "view-factory.h"

using namespace chat_client_controller;

ClientController::ClientController(int argc, char **argv) {
  ViewFactory factory;
  this->view = factory.CreateView(argc, argv);

  this->view->WaitForInternalThreadToExit();
}