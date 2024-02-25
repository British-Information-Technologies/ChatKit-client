#include "injector.h"

#include "gtkmm/box.h"
#include <memory>

#include "view-model/network-view-model.h"
#include "view/common/ui-util.h"
#include "view/main/right/add-server/add-server-box.h"
#include "view/main/right/add-server/join-button.h"
#include "view/observers/notifications/notification-observer.h"
#include "view/observers/notifications/vbox-notification-observer.h"

Gtk::Box* injector::inject_add_server_box(
    view::VboxNotificationObserver* append_contact,
    view::NotificationObserver* open_contents,
    std::shared_ptr<view_model::NetworkViewModel> network_vm) {
    Glib::RefPtr<Gtk::Builder> add_server_builder = Gtk::Builder::create();

    char* ip_address = (char*)malloc(sizeof(char[16]));
    char* port = (char*)malloc(sizeof(char[6]));

    view::UpdateBuilder(add_server_builder, "/view/res/add_server.ui");

    Glib::RefPtr<JoinButton> join_button = Glib::RefPtr<JoinButton>(add_server_builder->get_widget_derived<JoinButton>(add_server_builder, "joinButton", ip_address, port, append_contact, open_contents, network_vm));

    return add_server_builder->get_widget_derived<AddServer>(add_server_builder, "addServerBox", ip_address, port, join_button, network_vm);
}