#include "ClientController.h"
#include "ViewFactory.h"

using namespace chat_client_controller;

ClientController::ClientController(int argc, char **argv) {
     ViewFactory factory;
     this->view = factory.createView(argc, argv);

     this->view->waitForInternalThreadToExit();
}