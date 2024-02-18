#include "contact-list-notification-observer.h"

#include "glibmm/refptr.h"

#include "gtkmm/button.h"
#include "gtkmm/widget.h"
#include "view/main/left/shared/contact-list-box.h"
#include "view/observers/notifications/contact-list-notification-observer.h"
#include "view/observers/notifications/vbox-notification-observer.h"

view::ContactListNotificationObserver::ContactListNotificationObserver(
    const Glib::RefPtr<ContactListBox> contact_list_box)
    : VboxNotificationObserver(),
      contact_list_box(contact_list_box) {}

void view::ContactListNotificationObserver::Notify(Glib::RefPtr<Gtk::Button> contact) {
    contact_list_box->AppendContactToList(contact);
}