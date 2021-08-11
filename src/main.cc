#include <iostream>

#include "controller/client-controller.h"

using namespace chat_client_controller;

int main(int argc, char **argv) {
  ClientController client_controller(argc, argv);
  client_controller.Body();

  // create application
  // auto app = MainApplication::create();

  // enter main loop
  // app->run(argc, argv);
}
