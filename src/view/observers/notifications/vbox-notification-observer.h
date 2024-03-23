#ifndef VIEW_OBSERVERS_NOTIFICATIONS_VBOX_H_
#define VIEW_OBSERVERS_NOTIFICATIONS_VBOX_H_

#include "glibmm/refptr.h"
#include "gtkmm/box.h"
#include "gtkmm/widget.h"

namespace view {
class VboxNotificationObserver {
public:
    virtual ~VboxNotificationObserver() = default;

    virtual void Notify(const Glib::RefPtr<Gtk::Widget>) = 0;
};
} // namespace view

#endif