#include <functional>
#include <gtkmm-4.0/gtkmm.h>
#include <iostream>

#include "add-server-box.h"

#include "sigc++/functors/ptr_fun.h"
#include "view-model/network-view-model.h"
#include "view/observers/notifications/notification-factory.h"

using namespace view;

struct _AddServer {
    GtkBox parent_type;

    GtkEntry* serverCodeEntry;

    GtkBox* addServerProfileCardBox;

    GtkLabel* serverNameLabel;
    GtkLabel* serverOwnerLabel;

    GtkButton* joinButton;
};

G_DEFINE_TYPE(AddServer, add_server, GTK_TYPE_BOX)

static AddServer* add_server;

namespace {

const std::string DELIMITER = ":";

bool on_widget_key_pressed(guint keyval, guint _, Gdk::ModifierType state, std::shared_ptr<view_model::NetworkViewModel> network_vm) {
    if (keyval == GDK_KEY_Return) {
        std::string data(Glib::wrap(add_server->serverCodeEntry, true)->get_text());

        int pos = data.find(DELIMITER);
        if (pos != std::string::npos) {
            std::string ip_address = data.substr(0, pos);
            std::string port = data.erase(0, pos + DELIMITER.length());

            GtkWidget* profile_card_box = GTK_WIDGET(add_server->addServerProfileCardBox);
            network_vm->ConnectToServer(
                ip_address,
                port,
                GetNotification(
                    NotificationType::ProfileCard,
                    profile_card_box,
                    add_server->serverNameLabel,
                    add_server->serverOwnerLabel));
        }
    }

    return false;
}
} // namespace

static void add_server_dispose(GObject* gobject) {
    gtk_widget_dispose_template(GTK_WIDGET(gobject), ADD_SERVER_TYPE);

    G_OBJECT_CLASS(add_server_parent_class)->dispose(gobject);
}

static void add_server_class_init(AddServerClass* klass) {
    G_OBJECT_CLASS(klass)->dispose = add_server_dispose;

    GtkWidgetClass* widget_class = GTK_WIDGET_CLASS(klass);

    gtk_widget_class_set_template_from_resource(
        widget_class,
        "/view/res/add_server.ui");

    // bind widgets inside template file to class members
    gtk_widget_class_bind_template_child(widget_class, AddServer, serverCodeEntry);
    gtk_widget_class_bind_template_child(widget_class, AddServer, addServerProfileCardBox);
    gtk_widget_class_bind_template_child(widget_class, AddServer, serverNameLabel);
    gtk_widget_class_bind_template_child(widget_class, AddServer, serverOwnerLabel);
    gtk_widget_class_bind_template_child(widget_class, AddServer, joinButton);
}

static void add_server_init(AddServer* self) {
    gtk_widget_init_template(GTK_WIDGET(self));

    add_server = self;

    // It is now possible to access self->attributes
}

void set_server_code_entry(std::shared_ptr<view_model::NetworkViewModel> network_vm) {
    auto event_ck = Gtk::EventControllerKey::create();

    event_ck->signal_key_pressed().connect(
        sigc::bind(sigc::ptr_fun(&on_widget_key_pressed), network_vm),
        false);

    Glib::wrap(GTK_WIDGET(add_server), true)->add_controller(event_ck);
}

void set_join_button(std::function<void()> func) {
    Glib::wrap(
        add_server->joinButton,
        true)
        ->signal_clicked()
        .connect(func);
}