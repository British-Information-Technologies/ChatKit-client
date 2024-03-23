#include "injector.h"

#include "glibmm/refptr.h"
#include "gtkmm/box.h"
#include "gtkmm/button.h"
#include <memory.h>
#include <string>

#include "view-model/network-view-model.h"
#include "view/common/ui-util.h"
#include "view/main/left/server/add-server-button.h"
#include "view/main/left/server/server-list-box.h"
#include "view/main/left/server/server-profile-card-button.h"
#include "view/main/shared/contact-list-box.h"
#include "view/observers/notifications/notification-observer.h"
#include "view/observers/server-observables.h"

std::shared_ptr<Gtk::Button> injector::inject_server_profile_card(
    std::shared_ptr<view_model::NetworkViewModel> network_vm,
    const std::string& server_name,
    const std::string& server_owner,
    view::ServerObservables* observables,
    const std::string& ip_address,
    const std::string& port) {
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create();

    view::UpdateBuilder(builder, "/view/res/server_profile_card.ui");

    std::shared_ptr<ServerProfileCardButton> profile_card_button(
        builder->get_widget_derived<ServerProfileCardButton>(
            builder,
            "openServerButton",
            network_vm,
            server_name,
            server_owner,
            observables,
            ip_address,
            port));

    return profile_card_button;
}

Gtk::Box* injector::inject_server_list(view::NotificationObserver* show_add_server) {
    Glib::RefPtr<Gtk::Builder> server_list_builder = Gtk::Builder::create();

    view::UpdateBuilder(server_list_builder, "/view/res/server_list.ui");

    auto add_server_button = Glib::RefPtr<AddServerButton>(server_list_builder->get_widget_derived<AddServerButton>(server_list_builder, "addServerButton", show_add_server));

    auto contact_box = server_list_builder->get_object<Gtk::Box>("contactBox");

    auto contact_list_box = Glib::RefPtr<ContactListBox>(server_list_builder->get_widget_derived<ContactListBox>(server_list_builder, "contactListBox", contact_box));

    return server_list_builder->get_widget_derived<ServerListBox>(server_list_builder, "serverListBox", add_server_button, contact_list_box);
}