#include <gtkmm-4.0/gtkmm.h>

#include "server-list-box.h"

struct _ServerList {
    GtkBox parent_type;
};

G_DEFINE_TYPE(ServerList, server_list, GTK_TYPE_BOX)

static ServerList *server_list;

static void server_list_dispose(GObject *gobject) {
    gtk_widget_dispose_template(GTK_WIDGET(gobject), SERVER_LIST_TYPE);
    
    G_OBJECT_CLASS(server_list_parent_class)->dispose(gobject);
}

static void server_list_class_init(ServerListClass *klass) {
    G_OBJECT_CLASS(klass)->dispose = server_list_dispose;

    GtkWidgetClass *widget_class = GTK_WIDGET_CLASS(klass);
    
    gtk_widget_class_set_template_from_resource(
        widget_class,
        "/view/res/server_list.ui"
    );

    // bind widgets inside template file to class members
}

static void server_list_init(ServerList *self) {
    gtk_widget_init_template(GTK_WIDGET(self));

    server_list = self;

    // It is now possible to access self->attributes
}