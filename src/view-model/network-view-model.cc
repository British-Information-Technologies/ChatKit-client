#include <gtkmm-4.0/gtkmm.h>
#include <memory>
#include <string>
#include <iostream>

#include "network-view-model.h"

#include "model/network-model.h"

using namespace view_model;

NetworkViewModel::NetworkViewModel(
  std::shared_ptr<model::NetworkModel> model,
  std::function<void()> showDirectMessage
) {
  this->model = model;
  this->showDirectMessage = showDirectMessage;
  
  //this->model->Run(); // Seg faults
}

void NetworkViewModel::SendMessageObserver(std::string &data) {
  if (data.empty()) {
      return;
  }

  std::cout << "Message to send: " << data << std::endl;
  
  model->SendMessage("faked uuid", data); // TODO: currently faked, will use data model getUuid() or server,
}

void NetworkViewModel::OpenContactObserver() {
  model->CreateClientConnection(
    "faked uuid", // TODO: currently faked, will use data model getUuid() or server,
    "faked ip",   // TODO: currently faked, will use data model getIpAddress() or server,
    "faked port"  // TODO: currently faked, will use data model getPort() or server
  );

  showDirectMessage();
}