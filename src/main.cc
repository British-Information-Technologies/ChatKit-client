#include "controller/client-controller.h"

using namespace controller;

int main(int argc, char **argv) {
  ClientController client_controller;
  client_controller.Body(argc, argv);
}
