#include <gtkmm-4.0/gtkmm.h>
#include <functional>

#include "direct-message-box.h"

namespace {
    bool on_widget_key_pressed(guint keyval, guint _, Gdk::ModifierType state) {
        if (keyval == GDK_KEY_Return) {
            printf("Hello Mitch\n");
        }

        return false;
    }
}

struct _DirectMessage {
    GtkBox parent_type;

    GtkButton *contentButton;
    GtkEntry *messageEntry;
};

G_DEFINE_TYPE(DirectMessage, direct_message, GTK_TYPE_BOX)

static DirectMessage *direct_message;
static std::function<void()> message_observer;

static void direct_message_dispose(GObject *gobject) {
    gtk_widget_dispose_template(GTK_WIDGET(gobject), DIRECT_MESSAGE_TYPE);
    
    G_OBJECT_CLASS(direct_message_parent_class)->dispose(gobject);
}

static void direct_message_class_init(DirectMessageClass *klass) {
    G_OBJECT_CLASS(klass)->dispose = direct_message_dispose;

    GtkWidgetClass *widget_class = GTK_WIDGET_CLASS(klass);
    
    gtk_widget_class_set_template_from_resource(
        widget_class,
        "/view/res/direct_message.ui"
    );

    // bind widgets inside template file to class members
    gtk_widget_class_bind_template_child(widget_class, DirectMessage, contentButton);
    gtk_widget_class_bind_template_child(widget_class, DirectMessage, messageEntry);
}

static void direct_message_init(DirectMessage *self) {
    gtk_widget_init_template(GTK_WIDGET(self));

    direct_message = self;

    // It is now possible to access self->attributes
}

void set_message_entry(std::function<void()> func) {
    message_observer = func;

    auto event_ck = Gtk::EventControllerKey::create();
    
    event_ck->signal_key_pressed().connect(
        sigc::ptr_fun(&on_widget_key_pressed),
        false
    );

    Glib::wrap(GTK_WIDGET(direct_message), true)->add_controller(event_ck);
}
