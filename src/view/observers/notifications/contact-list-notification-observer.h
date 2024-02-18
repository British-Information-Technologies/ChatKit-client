#ifndef VIEW_OBSERVERS_NOTIFICATIONS_CONTACT_LIST_H_
#define VIEW_OBSERVERS_NOTIFICATIONS_CONTACT_LIST_H_

#include "glibmm/refptr.h"
#include "gtkmm/box.h"
#include "gtkmm/button.h"

#include "view/main/left/shared/contact-list-box.h"
#include "view/observers/notifications/vbox-notification-observer.h"

namespace view {
class ContactListNotificationObserver : public VboxNotificationObserver {
private:
    const Glib::RefPtr<ContactListBox> contact_list_box;

public:
    ContactListNotificationObserver(const Glib::RefPtr<ContactListBox> contact_list_box);

    void Notify(const Glib::RefPtr<Gtk::Button> contact);
};
} // namespace view

#endif