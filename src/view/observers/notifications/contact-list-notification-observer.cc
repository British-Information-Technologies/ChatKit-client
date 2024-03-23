#include "contact-list-notification-observer.h"

#include "glibmm/refptr.h"

#include "gtkmm/button.h"
#include "gtkmm/widget.h"
#include "view/main/shared/contact-list-box.h"
#include "view/main/shared/list-box.h"
#include "view/observers/notifications/contact-list-notification-observer.h"
#include "view/observers/notifications/vbox-notification-observer.h"

view::ContactListNotificationObserver::ContactListNotificationObserver(
    ListBox** list_box)
    : list_box(list_box) {}

void view::ContactListNotificationObserver::Notify(const Glib::RefPtr<Gtk::Widget> contact) {
    (*list_box)->AppendToList(ListType::Contact, contact);
}