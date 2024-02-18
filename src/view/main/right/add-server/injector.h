#ifndef VIEW_MAIN_RIGHT_ADD_SERVER_INJECTOR_H_
#define VIEW_MAIN_RIGHT_ADD_SERVER_INJECTOR_H_

#include "glibmm/refptr.h"
#include <memory>

#include "view-model/network-view-model.h"
#include "view/main/right/add-server/add-server-box.h"
#include "view/observers/notifications/notification-observer.h"

namespace injector {
const Glib::RefPtr<AddServer> inject_add_server_box(
    view::VboxNotificationObserver* append_contact,
    view::NotificationObserver* open_contents,
    std::shared_ptr<view_model::NetworkViewModel> network_vm);
} // namespace injector

#endif