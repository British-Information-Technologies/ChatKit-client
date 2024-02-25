#include "notification-factory.h"

#include "glibmm/refptr.h"
#include "view-model/network-view-model.h"
#include "view/observers/notifications/contact-list-notification-observer.h"
#include "view/observers/notifications/main-layout-notification-observer.h"
#include "view/observers/notifications/profile-card-notification-observer.h"
#include "view/observers/notifications/vbox-notification-observer.h"

#include <gtkmm-4.0/gtkmm.h>
#include <memory>

using namespace view;

NotificationObserver* view::GetNotification(
    NotificationType type,
    Gtk::Box** box_one,
    Gtk::Box** box_two,
    Gtk::Box** box_three,
    Gtk::Box** box_four) {
    switch (type) {
    case NotificationType::MainLayout: {
        return new MainLayoutNotificationObserver(box_one, box_two, box_three, box_four);
    }
    default:
        return nullptr;
    }
}

NotificationObserver* view::GetNotification(
    const NotificationType type,
    const Glib::RefPtr<Gtk::Widget> widget,
    const Glib::RefPtr<Gtk::Label> first,
    const Glib::RefPtr<Gtk::Label> second) {
    switch (type) {
    case NotificationType::ProfileCard: {
        return new ProfileCardNotificationObserver(widget, first, second);
    }
    default:
        return nullptr;
    }
}

VboxNotificationObserver* view::GetNotification(
    const NotificationType type,
    ContactListBox** contact_list_box) {
    return new ContactListNotificationObserver(contact_list_box);
}