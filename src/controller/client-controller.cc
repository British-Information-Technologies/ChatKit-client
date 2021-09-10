#include "client-controller.h"

#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include "networking/network-receiver.h"
#include "observers/addfriend-observer.h"
#include "observers/deletefriend-observer.h"
#include "observers/send-message-observer.h"
#include "view-factory.h"

using namespace controller;
using namespace controller_networking;
using namespace controller_observers;
using namespace model;
using namespace std;

void *ClientController::NetworkManager(void) {
  auto connections = model->LoadConnections();

  NetworkReceiver network_receiver(model, view, connections);
  network_receiver.listen();

  return 0;
}

void *ClientController::NetworkManagerHelper(void *context) {
  return ((ClientController *)context)->NetworkManager();
}

ClientController::ClientController(int argc, char **argv) {
  model = make_shared<ClientModel>();

  ViewFactory factory;
  view = factory.CreateView(argc, argv);
}

void ClientController::Body() {
  // setup the gui
  view->register_application();

  // add observers to buttons
  AddFriendObserver add_friend_observer(model, view);
  DeleteFriendObserver delete_friend_observer(model, view);
  SendMessageObserver send_message_observer(model, view);

  // enter main loop
  view->run();
}