#include "server-observables.h"

#include "view/observers/notifications/notification-observer.h"
#include "view/observers/notifications/vbox-notification-observer.h"

using namespace view;

ServerObservables::ServerObservables(
    NotificationObserver* open_contets,
    VboxNotificationObserver* messages,
    VboxNotificationObserver* connected_users)
    : open_contents(open_contets),
      messages(messages),
      connected_users(connected_users) {}

ServerObservables::ServerObservables(
    NotificationObserver* open_contets)
    : open_contents(open_contets) {}