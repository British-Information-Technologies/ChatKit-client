#include <gtkmm-4.0/gtkmm.h>

#define DIRECT_MESSAGE_TYPE direct_message_get_type()

struct _DirectMessage {
    GtkBox parent_type;
};

G_DECLARE_FINAL_TYPE(DirectMessage, direct_message, DIRECT, MESSAGE, GtkBox)
G_DEFINE_TYPE(DirectMessage, direct_message, GTK_TYPE_BOX)

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
    // gtk_widget_class_bind_template_child();
}

static void direct_message_init(DirectMessage *self) {
    gtk_widget_init_template(GTK_WIDGET(self));

    // It is now possible to access self->entry and self->button
}