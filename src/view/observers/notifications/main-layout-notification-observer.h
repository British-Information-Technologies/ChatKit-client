#ifndef VIEW_OBSERVERS_NOTIFICATIONS_MAIN_LAYOUT_H_
#define VIEW_OBSERVERS_NOTIFICATIONS_MAIN_LAYOUT_H_

#include "glibmm/refptr.h"
#include "gtkmm/box.h"
#include <string>

#include "view-model/network-view-model.h"
#include "view/observers/notifications/notification-observer.h"

namespace view {
class MainLayoutNotificationObserver : public NotificationObserver {
private:
    Gtk::Box** main_box;
    Gtk::Box** sub_box_one;
    Gtk::Box** sub_box_two;
    Gtk::Box** sub_box_three;

public:
    MainLayoutNotificationObserver(
        Gtk::Box** main_box,
        Gtk::Box** sub_box_one,
        Gtk::Box** sub_box_two,
        Gtk::Box** sub_box_three);

    void Notify(const std::string& alias, const std::string& owner);
};
} // namespace view

#endif