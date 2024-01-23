#ifndef VIEW_OBSERVERS_NOTIFICATIONS_H_
#define VIEW_OBSERVERS_NOTIFICATIONS_H_

#include <gtkmm-4.0/gtkmm/widget.h>

namespace view {
class NotificationObserver {
protected:
    GtkWidget* widget;

    GtkWidget* find_child(GtkWidget* parent, const gchar* name);

public:
    NotificationObserver(GtkWidget* widget);

    virtual ~NotificationObserver() = default;

    virtual void Notify(const std::string& alias, const std::string& owner) = 0;
};
} // namespace view

#endif