#ifndef VIEW_OBSERVERS_SERVER_OBSERVABLES_H_
#define VIEW_OBSERVERS_SERVER_OBSERVABLES_H_

#include "view/observers/notifications/notification-observer.h"
#include "view/observers/notifications/vbox-notification-observer.h"
#include <memory>

namespace view {
// todo: this is extremely unsafe and needs to be reworked
class ServerObservables {
public:
    std::unique_ptr<NotificationObserver> open_contents;

    std::unique_ptr<VboxNotificationObserver> messages;

    std::unique_ptr<VboxNotificationObserver> connected_users;

public:
    ServerObservables(
        NotificationObserver* open_contents,
        VboxNotificationObserver* messages,
        VboxNotificationObserver* connected_users);

    ServerObservables(
        NotificationObserver* open_contents);

    ~ServerObservables() = default;
};
} // namespace view

#endif