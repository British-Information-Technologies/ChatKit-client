#ifndef VIEW_MAIN_LEFT_FRIEND_INJECTOR_H_
#define VIEW_MAIN_LEFT_FRIEND_INJECTOR_H_

#include "gtkmm/box.h"
#include "gtkmm/button.h"
#include <memory.h>

#include "view-model/network-view-model.h"
#include "view/observers/notifications/notification-observer.h"

namespace injector {
std::shared_ptr<Gtk::Button> inject_friend_profile_card(
    std::shared_ptr<view_model::NetworkViewModel> network_vm,
    view::NotificationObserver* open_contents,
    const std::string& username,
    const std::string& type);

Gtk::Box* inject_friend_list(view::NotificationObserver* show_add_friend);
} // namespace injector

#endif
