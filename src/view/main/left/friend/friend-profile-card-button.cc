#include "friend-profile-card-button.h"

#include "glibmm/refptr.h"
#include "gtkmm/builder.h"
#include "gtkmm/button.h"
#include "gtkmm/label.h"
#include <memory>
#include <string>

#include "view-model/network-view-model.h"
#include "view/observers/notifications/notification-observer.h"

void FriendProfileCardButton::on_clicked() {
    const std::string fake_ip = "192.168.0.59"; // TODO: currently faked, will use data model getIpAddress() or server,
    const std::string fake_port = "5789";       // TODO: currently faked, will use data model getPort() or server

    network_vm->ConnectToClient(fake_ip, fake_port, notification);
}

FriendProfileCardButton::FriendProfileCardButton(
    BaseObjectType* cobject,
    const Glib::RefPtr<Gtk::Builder>& refBuilder,
    std::shared_ptr<view_model::NetworkViewModel> network_vm,
    view::NotificationObserver* notification,
    const std::string& username,
    const std::string& type) : Glib::ObjectBase("FriendProfileCardButton"), Gtk::Button(cobject), refBuilder(refBuilder), notification(notification), network_vm(network_vm) {
    this->username_label = this->refBuilder->get_object<Gtk::Label>("openChatUsernameLabel");
    this->username_label->set_label(username);

    this->chat_type_label = this->refBuilder->get_object<Gtk::Label>("openChatTypeLabel");
    this->chat_type_label->set_label(type);
}

FriendProfileCardButton::~FriendProfileCardButton() {}