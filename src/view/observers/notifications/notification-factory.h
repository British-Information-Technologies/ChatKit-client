#ifndef VIEW_OBSERVERS_NOTIFICATIONS_FACTORY_H_
#define VIEW_OBSERVERS_NOTIFICATIONS_FACTORY_H_

#include "view/observers/notifications/notification-observer.h"

#include <gtkmm-4.0/gtkmm/widget.h>

namespace view {
enum class NotificationType {
    ProfileCard,
};

NotificationObserver* GetNotification(
    NotificationType type,
    GtkWidget* widget,
    GtkLabel* first,
    GtkLabel* second);
} // namespace view

#endif
