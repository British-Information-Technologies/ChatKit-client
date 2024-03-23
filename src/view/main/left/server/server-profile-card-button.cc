#include "server-profile-card-button.h"

#include "glibmm/refptr.h"
#include "gtkmm/builder.h"
#include "gtkmm/button.h"
#include "gtkmm/label.h"
#include <memory>
#include <string>

#include "view-model/network-view-model.h"
#include "view/observers/server-observables.h"

void ServerProfileCardButton::on_clicked() {
    network_vm->ConnectToServer(
        ip_address,
        port,
        observables);
}

ServerProfileCardButton::ServerProfileCardButton(
    BaseObjectType* cobject,
    const Glib::RefPtr<Gtk::Builder>& refBuilder,
    std::shared_ptr<view_model::NetworkViewModel> network_vm,
    const std::string& name,
    const std::string& owner,
    view::ServerObservables* observables,
    const std::string& ip_address,
    const std::string& port) : refBuilder(refBuilder), network_vm(network_vm), ip_address(ip_address), port(port), Glib::ObjectBase("ServerProfileCardButton"), Gtk::Button(cobject), observables(observables) {
    name_label = this->refBuilder->get_object<Gtk::Label>("openServerNameLabel");
    name_label->set_label(name);

    owner_label = this->refBuilder->get_object<Gtk::Label>("openServerOwnerLabel");
    owner_label->set_label(owner);
}

ServerProfileCardButton::~ServerProfileCardButton() {}