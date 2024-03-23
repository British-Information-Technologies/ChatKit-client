#include "injector.h"

#include "glibmm/refptr.h"
#include "gtkmm/box.h"
#include "gtkmm/builder.h"
#include <memory>

#include "gtkmm/button.h"
#include "view-model/network-view-model.h"
#include "view/common/ui-util.h"
#include "view/main/right/direct-message/direct-message-box.h"
#include "view/main/right/direct-message/message-entry.h"
#include "view/main/shared/contact-list-box.h"
#include "view/main/shared/message-list-box.h"
#include "view/observers/notifications/notification-factory.h"
#include "view/observers/notifications/vbox-notification-observer.h"
#include "view/observers/workers/worker-observer.h"

DirectMessage* injector::inject_direct_message_box(view::WorkerObserver* send_message) {
    Glib::RefPtr<Gtk::Builder> direct_message_builder = Gtk::Builder::create();

    view::UpdateBuilder(direct_message_builder, "/view/res/direct_message.ui");

    // MessageListBox Setup
    Glib::RefPtr<Gtk::Box> message_box = direct_message_builder->get_object<Gtk::Box>("messageBox");

    Glib::RefPtr<Gtk::Button> content_button = direct_message_builder->get_object<Gtk::Button>("contentButton");

    Glib::RefPtr<MessageEntry> message_entry = Glib::RefPtr<MessageEntry>(direct_message_builder->get_widget_derived<MessageEntry>(direct_message_builder, "messageEntry", send_message));

    Glib::RefPtr<MessageListBox> message_list_box = Glib::RefPtr<MessageListBox>(direct_message_builder->get_widget_derived<MessageListBox>(direct_message_builder, "messageListBox", message_box, content_button, message_entry));

    // ContactListBox Setup
    Glib::RefPtr<Gtk::Box> connected_clients = direct_message_builder->get_object<Gtk::Box>("connectedClients");

    Glib::RefPtr<ContactListBox> contact_list_box = Glib::RefPtr<ContactListBox>(direct_message_builder->get_widget_derived<ContactListBox>(direct_message_builder, "contactListBox", connected_clients));

    // DirectMessage Setup
    return direct_message_builder->get_widget_derived<DirectMessage>(direct_message_builder, "directMessageBox", message_list_box, contact_list_box);
}