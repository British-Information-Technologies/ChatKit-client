#ifndef VIEW_OBSERVERS_NOTIFICATIONS_PROFILE_CARD_H_
#define VIEW_OBSERVERS_NOTIFICATIONS_PROFILE_CARD_H_

#include "view/observers/notifications/notification-observer.h"

#include <gtkmm-4.0/gtkmm/widget.h>

namespace view {
class ProfileCardNotificationObserver : public NotificationObserver {
private:
    GtkLabel* first;
    GtkLabel* second;

public:
    ProfileCardNotificationObserver(
        GtkWidget* widget,
        GtkLabel* first,
        GtkLabel* second);

    void Notify(const std::string& alias, const std::string& owner);

private:
    void SetFirstLabel(const std::string& text);

    void SetSecondLabel(const std::string& text);
};
} // namespace view

#endif