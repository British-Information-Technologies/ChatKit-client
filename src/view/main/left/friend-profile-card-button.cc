#include <gtkmm-4.0/gtkmm.h>
#include <memory>
#include <functional>

#include "friend-profile-card-button.h"

#include "view-model/network-view-model.h"

FriendProfileCardButton::FriendProfileCardButton(
    BaseObjectType *cobject, 
    const Glib::RefPtr<Gtk::Builder> &refBuilder,
    std::shared_ptr<view_model::NetworkViewModel> network_vm,
    const std::string &username,
    const std::string &type
): Glib::ObjectBase("FriendProfileCardButton"), Gtk::Button(cobject)
{
    this->refBuilder = refBuilder;

    this->signal_clicked().connect(
        sigc::mem_fun(
            *network_vm,
            &view_model::NetworkViewModel::OpenContactObserver
        )
    );

    this->username_label = this->refBuilder->get_object<Gtk::Label>("openChatUsernameLabel");
    this->username_label->set_label(username);

    this->chat_type_label = this->refBuilder->get_object<Gtk::Label>("openChatTypeLabel");
    this->chat_type_label->set_label(type);
}

FriendProfileCardButton::~FriendProfileCardButton() {}