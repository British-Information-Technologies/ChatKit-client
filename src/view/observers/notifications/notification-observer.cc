#include "notification-observer.h"

#include <cstddef>
#include <gtkmm-4.0/gtkmm.h>
#include <gtkmm-4.0/gtkmm/binlayout.h>
#include <gtkmm-4.0/gtkmm/widget.h>

using namespace view;

NotificationObserver::NotificationObserver(GtkWidget* widget) : widget(widget) {}

GtkWidget* NotificationObserver::find_child(GtkWidget* parent, const char* name) {
    GtkWidget* child = gtk_widget_get_first_child(parent);

    if (child != NULL) {
        GtkWidget* next;
        while ((next = gtk_widget_get_next_sibling(child)) != NULL) {
            GtkWidget* result = find_child(next, name);
            if (result != NULL) {
                return result;
            }

            if (strcmp(gtk_widget_get_name(next), name) == 0) {
                return next;
            }
        }
    }

    return NULL;
}