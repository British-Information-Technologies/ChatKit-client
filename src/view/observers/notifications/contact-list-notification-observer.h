#ifndef VIEW_OBSERVERS_NOTIFICATIONS_CONTACT_LIST_H_
#define VIEW_OBSERVERS_NOTIFICATIONS_CONTACT_LIST_H_

#include "glibmm/refptr.h"
#include "gtkmm/box.h"
#include "gtkmm/button.h"

#include "gtkmm/widget.h"
#include "view/main/shared/contact-list-box.h"
#include "view/main/shared/list-box.h"
#include "view/observers/notifications/vbox-notification-observer.h"

namespace view {
class ContactListNotificationObserver : public VboxNotificationObserver {
private:
    ListBox** list_box;

public:
    ContactListNotificationObserver(ListBox** list_box);

    void Notify(const Glib::RefPtr<Gtk::Widget> contact);
};
} // namespace view

#endif