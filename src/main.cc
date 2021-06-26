#include <iostream>

#include "MainApplication.h"
#include "controller/client-controller.h"

using namespace chat_client_controller;

int main(int argc, char **argv) {
  // create application
  auto app = MainApplication::create();

  // increases reference count.
  app->hold();

  // enter main loop
  app->run(argc, argv);
}
