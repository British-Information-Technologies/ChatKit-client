#ifndef VIEW_OBSERVERS_NOTIFICATIONS_MESSAGE_LIST_H_
#define VIEW_OBSERVERS_NOTIFICATIONS_MESSAGE_LIST_H_

#include "glibmm/refptr.h"
#include "gtkmm/box.h"
#include "gtkmm/button.h"

#include "gtkmm/widget.h"
#include "view/main/shared/list-box.h"
#include "view/main/shared/message-list-box.h"
#include "view/observers/notifications/vbox-notification-observer.h"

namespace view {
class MessageListNotificationObserver : public VboxNotificationObserver {
private:
    ListBox** list_box;

public:
    MessageListNotificationObserver(ListBox** list_box);

    void Notify(const Glib::RefPtr<Gtk::Widget> message);
};
} // namespace view

#endif