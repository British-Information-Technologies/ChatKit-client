#include "notification-factory.h"

#include "view/observers/notifications/profile-card-notification-observer.h"

#include <gtkmm-4.0/gtkmm/widget.h>
#include <memory>

using namespace view;

NotificationObserver* view::GetNotification(
    NotificationType type,
    GtkWidget* widget,
    GtkLabel* first,
    GtkLabel* second) {
    switch (type) {
    case NotificationType::ProfileCard: {
        return new ProfileCardNotificationObserver(widget, first, second);
    }
    }
}