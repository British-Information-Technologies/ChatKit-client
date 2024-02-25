#ifndef VIEW_OBSERVERS_NOTIFICATIONS_FACTORY_H_
#define VIEW_OBSERVERS_NOTIFICATIONS_FACTORY_H_

#include "glibmm/refptr.h"
#include "gtkmm/widget.h"

#include "view-model/network-view-model.h"
#include "view/main/left/shared/contact-list-box.h"
#include "view/observers/notifications/notification-observer.h"
#include "view/observers/notifications/vbox-notification-observer.h"

namespace view {
enum class NotificationType {
    ProfileCard,
    MainLayout,
    ContactList,
};

NotificationObserver* GetNotification(
    NotificationType type,
    Gtk::Box** box_one,
    Gtk::Box** box_two,
    Gtk::Box** box_three,
    Gtk::Box** box_four);

NotificationObserver* GetNotification(
    const NotificationType type,
    const Glib::RefPtr<Gtk::Widget> widget,
    const Glib::RefPtr<Gtk::Label> first,
    const Glib::RefPtr<Gtk::Label> second);

VboxNotificationObserver* GetNotification(
    const NotificationType type,
    ContactListBox** contact_list_box);
} // namespace view

#endif
