#ifndef VIEW_MAIN_LEFT_FRIEND_INJECTOR_H_
#define VIEW_MAIN_LEFT_FRIEND_INJECTOR_H_

#include "glibmm/refptr.h"
#include "gtkmm/button.h"
#include <memory.h>

#include "view-model/network-view-model.h"
#include "view/main/left/friend/friend-list-box.h"
#include "view/observers/notifications/notification-observer.h"

namespace injector {
std::shared_ptr<Gtk::Button> inject_friend_profile_card(
    std::shared_ptr<view_model::NetworkViewModel> network_vm,
    view::NotificationObserver* open_contents,
    const std::string& username,
    const std::string& type);

Glib::RefPtr<FriendListBox> inject_friend_list(
    view::NotificationObserver* show_add_friend);
} // namespace injector

#endif
