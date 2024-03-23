#include "message-list-notification-observer.h"

#include "glibmm/refptr.h"

#include "gtkmm/button.h"
#include "gtkmm/widget.h"
#include "view/main/shared/list-box.h"
#include "view/main/shared/message-list-box.h"
#include "view/observers/notifications/contact-list-notification-observer.h"
#include "view/observers/notifications/vbox-notification-observer.h"

view::MessageListNotificationObserver::MessageListNotificationObserver(
    ListBox** list_box)
    : VboxNotificationObserver(),
      list_box(list_box) {}

void view::MessageListNotificationObserver::Notify(const Glib::RefPtr<Gtk::Widget> message) {
    (*list_box)->AppendToList(ListType::Message, message);
}