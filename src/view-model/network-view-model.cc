#include <gtkmm-4.0/gtkmm.h>
#include <memory>
#include <string>

#include "network-view-model.h"

#include "model/network-model.h"

using namespace view_model;

NetworkViewModel::NetworkViewModel(
  std::shared_ptr<model::NetworkModel> model,
  Glib::RefPtr<Gtk::Entry> msg_entry
) {
  this->model = model;
  this->msg_entry = msg_entry;
  
  //this->model->Run(); // Seg faults
}

void NetworkViewModel::SendMessageObserver() {
  if (msg_entry->get_text_length() == 0) {
      return;
  }

  printf("Message to send: %s\n", msg_entry->get_text().c_str());
  
  std::string msg = msg_entry->get_text().c_str();
  model->SendMessage(1, msg);
}