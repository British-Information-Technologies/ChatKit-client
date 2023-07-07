#ifndef VIEW_MODEL_NETWORK_H_
#define VIEW_MODEL_NETWORK_H_

#include <gtkmm-4.0/gtkmm.h>

#include "../model/network-model.h"

namespace view_model {
  class NetworkViewModel {
    private:
      std::shared_ptr<model::NetworkModel> model;

      // Bindings
      Glib::RefPtr<Gtk::Entry> msg_entry;

    public:
      NetworkViewModel(Glib::RefPtr<Gtk::Entry> msg_entry);

      void SendMessageObserver();
  };
}  // namespace view_model

#endif