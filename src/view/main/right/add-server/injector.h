#ifndef VIEW_MAIN_RIGHT_ADD_SERVER_INJECTOR_H_
#define VIEW_MAIN_RIGHT_ADD_SERVER_INJECTOR_H_

#include <memory>

#include "gtkmm/box.h"

#include "view-model/network-view-model.h"
#include "view/observers/notifications/notification-observer.h"
#include "view/observers/notifications/vbox-notification-observer.h"
#include "view/observers/server-observables.h"

namespace injector {
Gtk::Box* inject_add_server_box(
    view::VboxNotificationObserver* append_contact,
    view::ServerObservables* observables,
    std::shared_ptr<view_model::NetworkViewModel> network_vm);
} // namespace injector

#endif