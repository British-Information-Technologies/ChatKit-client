#ifndef VIEW_MAIN_RIGHT_ADD_FRIEND_INJECTOR_H_
#define VIEW_MAIN_RIGHT_ADD_FRIEND_INJECTOR_H_

#include "glibmm/refptr.h"

#include "view-model/network-view-model.h"
#include "view/main/right/add-friend/add-friend-box.h"
#include "view/observers/notifications/notification-observer.h"
#include "view/observers/notifications/vbox-notification-observer.h"

namespace injector {
const Glib::RefPtr<AddFriend> inject_add_friend_box(
    view::VboxNotificationObserver* append_contact,
    view::NotificationObserver* open_contents,
    std::shared_ptr<view_model::NetworkViewModel> network_vm);
} // namespace injector

#endif