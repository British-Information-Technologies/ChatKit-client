#ifndef VIEW_MAIN_LEFT_SERVER_INJECTOR_H_
#define VIEW_MAIN_LEFT_SERVER_INJECTOR_H_

#include "glibmm/refptr.h"
#include "gtkmm/button.h"
#include <memory.h>
#include <string>

#include "view-model/network-view-model.h"
#include "view/main/left/server/server-list-box.h"
#include "view/observers/notifications/notification-observer.h"

namespace injector {
std::shared_ptr<Gtk::Button> inject_server_profile_card(
    std::shared_ptr<view_model::NetworkViewModel> network_vm,
    const std::string& server_name,
    const std::string& server_owner,
    view::NotificationObserver* open_contents,
    const std::string& ip_address,
    const std::string& port);

const Glib::RefPtr<ServerListBox> inject_server_list(
    view::NotificationObserver* show_add_server);
} // namespace injector

#endif
