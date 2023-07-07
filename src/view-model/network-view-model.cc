#include <gtkmm-4.0/gtkmm.h>
#include <memory>
#include <string>

#include "network-view-model.h"

#include "../model/network-model.h"

using namespace view_model;
using namespace model;

NetworkViewModel::NetworkViewModel(
  Glib::RefPtr<Gtk::Entry> msg_entry
) {
  model = std::make_shared<NetworkModel>();

  this->msg_entry = msg_entry;
  
  model->Run();
}

void NetworkViewModel::SendMessageObserver() {
  if (msg_entry->get_text_length() == 0) {
      return;
  }

  printf("Message to send: %s\n", msg_entry->get_text().c_str());
  
  std::string msg = msg_entry->get_text().c_str();
  model->SendMessage(1, msg);
}