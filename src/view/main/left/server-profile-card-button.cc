#include <functional>
#include <gtkmm-4.0/gtkmm.h>
#include <memory>

#include "server-profile-card-button.h"

#include "view-model/network-view-model.h"

ServerProfileCardButton::ServerProfileCardButton(
    BaseObjectType* cobject,
    const Glib::RefPtr<Gtk::Builder>& refBuilder,
    std::shared_ptr<view_model::NetworkViewModel> network_vm,
    const std::string& name,
    const std::string& type) : Glib::ObjectBase("ServerProfileCardButton"), Gtk::Button(cobject) {
    this->refBuilder = refBuilder;

    this->signal_clicked().connect(
        sigc::mem_fun(
            *network_vm,
            &view_model::NetworkViewModel::OpenContactObserver));

    name_label = this->refBuilder->get_object<Gtk::Label>("openServerNameLabel");
    name_label->set_label(name);

    type_label = this->refBuilder->get_object<Gtk::Label>("openServerTypeLabel");
    type_label->set_label(type);
}

ServerProfileCardButton::~ServerProfileCardButton() {}