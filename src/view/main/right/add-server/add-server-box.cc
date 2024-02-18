#include "add-server-box.h"

#include "glibmm/refptr.h"
#include "gtkmm/box.h"
#include "gtkmm/builder.h"
#include "gtkmm/entry.h"
#include "gtkmm/eventcontrollerkey.h"
#include "gtkmm/label.h"
#include "sigc++/functors/mem_fun.h"
#include <memory>

#include "view-model/network-view-model.h"
#include "view/main/right/add-server/join-button.h"
#include "view/observers/notifications/notification-factory.h"
#include "view/observers/notifications/notification-observer.h"

using namespace view;

const std::string DELIMITER = ":";

AddServer::AddServer(
    BaseObjectType* cobject,
    const Glib::RefPtr<Gtk::Builder>& refBuilder,
    char* ip_address,
    char* port,
    const Glib::RefPtr<JoinButton> join_button,
    std::shared_ptr<view_model::NetworkViewModel> network_vm)
    : Glib::ObjectBase("AddServer"),
      Gtk::Box(cobject),
      refBuilder(refBuilder),
      ip_address(ip_address),
      port(port),
      network_vm(network_vm),
      server_code_entry(refBuilder->get_object<Gtk::Entry>("serverCodeEntry")),
      add_server_profile_card_box(refBuilder->get_object<Gtk::Box>("addServerProfileCardBox")),
      server_name_label(refBuilder->get_object<Gtk::Label>("serverNameLabel")),
      server_owner_label(refBuilder->get_object<Gtk::Label>("serverOwnerLabel")),
      join_button(join_button),
      notification(GetNotification(
          NotificationType::ProfileCard,
          add_server_profile_card_box,
          server_name_label,
          server_owner_label)),
      event_ck(Gtk::EventControllerKey::create()) {
    event_ck->signal_key_pressed()
        .connect(
            sigc::mem_fun(*this, &AddServer::EnterPressed),
            false);

    add_controller(event_ck);
}

bool AddServer::EnterPressed(guint keyval, guint _, Gdk::ModifierType state) {
    if (keyval == GDK_KEY_Return) {
        std::string data(server_code_entry->get_text());

        int pos = data.find(DELIMITER);

        if (pos != std::string::npos) {
            const std::string ip_address = data.substr(0, pos);
            memcpy(this->ip_address, ip_address.c_str(), ip_address.length() + 1);

            const std::string port = data.erase(0, pos + DELIMITER.length());
            memcpy(this->port, port.c_str(), port.length() + 1);

            network_vm->ConnectToServer(
                this->ip_address,
                this->port,
                this->notification.get());
        }
    }

    return false;
}

AddServer::~AddServer() {
    free(ip_address);
    free(port);
}