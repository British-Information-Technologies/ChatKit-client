#include "send-invite-button.h"

#include "glibmm/refptr.h"
#include "gtkmm/button.h"
#include <memory>

#include "view-model/network-view-model.h"
#include "view/main/left/friend/injector.h"
#include "view/observers/notifications/notification-observer.h"
#include "view/observers/notifications/vbox-notification-observer.h"

void SendInviteButton::on_clicked() {
    // TODO: use uuid to load user data from local storage (names, etc)
    const std::string username = "fake username";
    const std::string type = "fake type";

    // TODO: currently hard coded and faked, eventually change with net vm
    auto profile_card_button = injector::inject_friend_profile_card(
        network_vm,
        open_contents.get(),
        username,
        type);

    append_contact->Notify(profile_card_button);
}

SendInviteButton::SendInviteButton(
    BaseObjectType* cobject,
    const Glib::RefPtr<Gtk::Builder>& refBuilder,
    view::VboxNotificationObserver* append_contact,
    view::NotificationObserver* open_contents,
    std::shared_ptr<view_model::NetworkViewModel> network_vm)
    : Glib::ObjectBase("SendFriendInviteButton"),
      Gtk::Button(cobject),
      refBuilder(refBuilder),
      append_contact(append_contact),
      open_contents(open_contents),
      network_vm(network_vm) {}