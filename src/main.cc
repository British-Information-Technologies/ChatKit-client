#include <iostream>

#include "controller/client-controller.h"

using namespace controller;

int main(int argc, char **argv) {
  ClientController client_controller(argc, argv);
  client_controller.Body();
}