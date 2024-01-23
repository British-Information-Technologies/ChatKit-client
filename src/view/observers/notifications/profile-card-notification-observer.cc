#include "profile-card-notification-observer.h"

#include <fmt/core.h>
#include <gtkmm-4.0/gtkmm.h>
#include <gtkmm-4.0/gtkmm/widget.h>

#include "view/style/font-sizes.h"
#include "view/style/formats.h"

using namespace view;

ProfileCardNotificationObserver::ProfileCardNotificationObserver(
    GtkWidget* widget,
    GtkLabel* first,
    GtkLabel* second)
    : NotificationObserver(widget), first(first), second(second) {}

void ProfileCardNotificationObserver::Notify(const std::string& alias, const std::string& owner) {
    if (Glib::wrap(widget, true)->is_visible()) {
        gtk_widget_set_visible(
            widget,
            false);
        return;
    }

    SetFirstLabel(alias);
    SetSecondLabel(owner);

    gtk_widget_set_visible(
        widget,
        true);
}

void ProfileCardNotificationObserver::SetFirstLabel(const std::string& text) {
    Glib::wrap(first, true)->set_label(SpanWithSize(FONT_MEDIUM, text));
}

void ProfileCardNotificationObserver::SetSecondLabel(const std::string& text) {
    Glib::wrap(second, true)->set_label(SpanWithSize(FONT_SMALL, text));
}