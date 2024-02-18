#include "injector.h"

#include "glibmm/refptr.h"
#include "gtkmm/button.h"
#include <memory.h>
#include <string>

#include "view-model/network-view-model.h"
#include "view/common/ui-util.h"
#include "view/main/left/friend/add-friend-button.h"
#include "view/main/left/friend/friend-list-box.h"
#include "view/main/left/friend/friend-profile-card-button.h"
#include "view/observers/notifications/notification-observer.h"

std::shared_ptr<Gtk::Button> injector::inject_friend_profile_card(
    std::shared_ptr<view_model::NetworkViewModel> network_vm,
    view::NotificationObserver* open_contents,
    const std::string& username,
    const std::string& type) {
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create();

    view::UpdateBuilder(builder, "/view/res/friend_profile_card.ui");

    std::shared_ptr<FriendProfileCardButton> profile_card_button(
        builder->get_widget_derived<FriendProfileCardButton>(
            builder,
            "openChatButton",
            network_vm,
            open_contents,
            username,
            type));

    return profile_card_button;
}

Glib::RefPtr<FriendListBox> injector::inject_friend_list(
    view::NotificationObserver* show_add_friend) {
    Glib::RefPtr<Gtk::Builder> friend_list_builder = Gtk::Builder::create();

    view::UpdateBuilder(friend_list_builder, "/view/res/friend_list.ui");

    auto add_friend_button = Glib::RefPtr<AddFriendButton>(friend_list_builder->get_widget_derived<AddFriendButton>(friend_list_builder, "addFriendButton", show_add_friend));

    return Glib::RefPtr<FriendListBox>(friend_list_builder->get_widget_derived<FriendListBox>(friend_list_builder, "friendListBox", add_friend_button));
}