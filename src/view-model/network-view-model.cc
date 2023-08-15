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
}

void NetworkViewModel::SendMessageObserver(std::string &data) {
  if (data.empty()) {
      return;
  }

  std::cout << "Message to send: " << data << std::endl;
  
  const std::string time("fake time"); // TODO
  const std::string date("fake date"); // TODO
  
  model->SendClientMessage("faked uuid", time, date, data); // TODO: currently faked, will use data model getUuid() or server,
}

void NetworkViewModel::OpenContactObserver() {
  model->CreateClientConnection(
    "faked uuid", // TODO: currently faked, will use data model getUuid() or server,
    "localhost",   // TODO: currently faked, will use data model getIpAddress() or server,
    "5789"  // TODO: currently faked, will use data model getPort() or server
  );

  showDirectMessage();
}