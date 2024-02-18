#ifndef VIEW_OBSERVERS_NOTIFICATIONS_PROFILE_CARD_H_
#define VIEW_OBSERVERS_NOTIFICATIONS_PROFILE_CARD_H_

#include "glibmm/refptr.h"
#include "gtkmm/label.h"
#include <string>

#include "view/observers/notifications/notification-observer.h"

namespace view {
class ProfileCardNotificationObserver : public NotificationObserver {
private:
    const Glib::RefPtr<Gtk::Widget> widget;
    const Glib::RefPtr<Gtk::Label> first;
    const Glib::RefPtr<Gtk::Label> second;

public:
    ProfileCardNotificationObserver(
        const Glib::RefPtr<Gtk::Widget> widget,
        const Glib::RefPtr<Gtk::Label> first,
        const Glib::RefPtr<Gtk::Label> second);

    void Notify(const std::string& alias, const std::string& owner);

private:
    void SetFirstLabel(const std::string& text);

    void SetSecondLabel(const std::string& text);
};
} // namespace view

#endif