#include "injector.h"

#include "glibmm/refptr.h"

#include "view-model/network-view-model.h"
#include "view/common/ui-util.h"
#include "view/main/right/add-friend/add-friend-box.h"
#include "view/main/right/add-friend/send-invite-button.h"
#include "view/observers/notifications/notification-observer.h"
#include "view/observers/notifications/vbox-notification-observer.h"
#include "view/observers/workers/worker-observer.h"

const Glib::RefPtr<AddFriend> injector::inject_add_friend_box(
    view::VboxNotificationObserver* append_contact,
    view::NotificationObserver* open_contents,
    std::shared_ptr<view_model::NetworkViewModel> network_vm) {
    Glib::RefPtr<Gtk::Builder> add_friend_builder = Gtk::Builder::create();

    view::UpdateBuilder(add_friend_builder, "/view/res/add_friend.ui");

    Glib::RefPtr<SendInviteButton> send_invite_button = Glib::RefPtr<SendInviteButton>(add_friend_builder->get_widget_derived<SendInviteButton>(add_friend_builder, "sendInviteButton", append_contact, open_contents, network_vm));

    return Glib::RefPtr<AddFriend>(add_friend_builder->get_widget_derived<AddFriend>(add_friend_builder, "addFriendBox", send_invite_button));
}