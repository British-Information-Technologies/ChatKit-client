#include "profile-card-notification-observer.h"

#include "glibmm/refptr.h"
#include "gtkmm/label.h"
#include "view/style/font-sizes.h"
#include "view/style/formats.h"
#include <string>

#include "view/observers/notifications/notification-observer.h"

using namespace view;

ProfileCardNotificationObserver::ProfileCardNotificationObserver(
    const Glib::RefPtr<Gtk::Widget> widget,
    const Glib::RefPtr<Gtk::Label> first,
    const Glib::RefPtr<Gtk::Label> second)
    : NotificationObserver(), widget(widget), first(first), second(second) {}

void ProfileCardNotificationObserver::Notify(const std::string& alias, const std::string& owner) {
    if (widget->is_visible()) {
        widget->hide();
        return;
    }

    SetFirstLabel(alias);
    SetSecondLabel(owner);

    widget->show();
}

void ProfileCardNotificationObserver::SetFirstLabel(const std::string& text) {
    first->set_label(SpanWithSize(FONT_MEDIUM, text));
}

void ProfileCardNotificationObserver::SetSecondLabel(const std::string& text) {
    second->set_label(SpanWithSize(FONT_SMALL, text));
}