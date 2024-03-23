#include "join-button.h"

#include "glibmm/refptr.h"
#include "gtkmm/builder.h"
#include "gtkmm/button.h"
#include "gtkmm/label.h"
#include <memory>

#include "view-model/network-view-model.h"
#include "view/main/left/server/injector.h"
#include "view/observers/notifications/notification-observer.h"
#include "view/observers/server-observables.h"

void JoinButton::on_clicked() {
    auto profile_card_button = injector::inject_server_profile_card(
        network_vm,
        server_name_label->get_text(),
        server_owner_label->get_text(),
        observables.get(),
        ip_address,
        port);

    append_contact->Notify(profile_card_button);
}

JoinButton::JoinButton(
    BaseObjectType* cobject,
    const Glib::RefPtr<Gtk::Builder>& refBuilder,
    char* ip_address,
    char* port,
    view::VboxNotificationObserver* append_contact,
    view::ServerObservables* observables,
    std::shared_ptr<view_model::NetworkViewModel> network_vm)
    : Glib::ObjectBase("JoinServerButton"),
      Gtk::Button(cobject),
      refBuilder(refBuilder),
      ip_address(ip_address),
      port(port),
      append_contact(append_contact),
      observables(observables),
      network_vm(network_vm),
      server_name_label(refBuilder->get_object<Gtk::Label>("serverNameLabel")),
      server_owner_label(refBuilder->get_object<Gtk::Label>("serverOwnerLabel")) {}