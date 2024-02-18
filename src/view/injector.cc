#include <functional>
#include <gtkmm-4.0/gtkmm.h>
#include <iostream>
#include <memory>

#include "glibmm/refptr.h"
#include "gtkmm/box.h"
#include "gtkmm/widget.h"
#include "injector.h"

#include "sigc++/functors/mem_fun.h"
#include "view-model/account-view-model.h"
#include "view-model/injector.h"
#include "view-model/network-view-model.h"

#include "view/login/login-application-window.h"

#include "view/main/left/friend/injector.h"
#include "view/main/left/profile/injector.h"
#include "view/main/left/server/injector.h"
#include "view/main/left/server/server-list-box.h"
#include "view/main/main-application-window.h"

#include "view/main/left/friend/friend-list-box.h"
#include "view/main/left/friend/friend-profile-card-button.h"
#include "view/main/left/profile/profile-card-box.h"
#include "view/main/left/server/server-list-box.h"
#include "view/main/left/server/server-profile-card-button.h"

#include "view/common/ui-util.h"
#include "view/main/right/add-friend/add-friend-box.h"
#include "view/main/right/add-friend/injector.h"
#include "view/main/right/add-server/add-server-box.h"
#include "view/main/right/add-server/injector.h"
#include "view/main/right/direct-message/direct-message-box.h"
#include "view/main/right/direct-message/injector.h"
#include "view/main/right/home-page-box.h"
#include "view/observers/notifications/notification-factory.h"
#include "view/observers/notifications/notification-observer.h"
#include "view/observers/workers/worker-factory.h"

using namespace view;

std::shared_ptr<Gtk::ApplicationWindow> Injector::inject_login(
    std::function<void(int)> setViewState) {
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create();

    UpdateBuilder(builder, "/view/res/login.ui");

    std::shared_ptr<view_model::AccountViewModel>
        account_vm = view_model::Injector::inject_account_vm(
            setViewState);

    std::shared_ptr<Gtk::ApplicationWindow> login_window(
        builder->get_widget_derived<LoginApplicationWindow>(
            builder,
            "loginWindow",
            account_vm));

    return login_window;
}

std::shared_ptr<Gtk::ApplicationWindow> Injector::inject_main() {
    // create network view model
    std::shared_ptr<view_model::NetworkViewModel> network_vm = view_model::Injector::inject_network_vm();

    // define widget types
    Glib::RefPtr<FriendListBox> friend_list;
    Glib::RefPtr<ServerListBox> server_list;
    Glib::RefPtr<ProfileCardBox> profile_card;
    Glib::RefPtr<AddFriend> add_friend;
    Glib::RefPtr<AddServer> add_server;
    Glib::RefPtr<HomePage> home_page;
    Glib::RefPtr<DirectMessage> direct_msg;

    // create observers
    auto show_messages = view::GetNotification(
        NotificationType::MainLayout,
        direct_msg,
        add_friend,
        add_server,
        home_page);

    auto show_add_friend = view::GetNotification(
        NotificationType::MainLayout,
        add_friend,
        direct_msg,
        add_server,
        home_page);

    auto show_add_server = view::GetNotification(
        NotificationType::MainLayout,
        add_server,
        add_friend,
        direct_msg,
        home_page);

    auto append_friend = view::GetNotification(NotificationType::ContactList, friend_list);

    auto append_server = view::GetNotification(NotificationType::ContactList, server_list);

    auto send_message = view::GetWorker(WorkerType::SendMessage, network_vm);

    // ensure custom types have been registered with the type system
    Glib::RefPtr<Gtk::Builder> homepage_builder = Gtk::Builder::create();

    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create();

    UpdateBuilder(homepage_builder, "/view/res/homepage.ui");
    UpdateBuilder(builder, "/view/res/main.ui");

    // load ui files for main window
    auto left_pane = builder->get_object<Gtk::Box>("leftPane");

    friend_list = injector::inject_friend_list(show_add_friend);

    server_list = injector::inject_server_list(show_add_server);

    profile_card = injector::inject_profile_card_box();

    left_pane->append(*friend_list);
    left_pane->append(*server_list);
    left_pane->append(*profile_card);

    const auto right_pane = builder->get_object<Gtk::Box>("rightPane");

    home_page = Glib::RefPtr<HomePage>(homepage_builder->get_widget_derived<HomePage>(homepage_builder, "homepageBox"));

    direct_msg = injector::inject_direct_message_box(send_message);

    add_friend = injector::inject_add_friend_box(append_friend, show_messages, network_vm);

    add_server = injector::inject_add_server_box(append_server, show_messages, network_vm);

    // add widgets to main window
    right_pane->append(*home_page);
    right_pane->append(*direct_msg);
    right_pane->append(*add_friend);
    right_pane->append(*add_server);

    // create main window
    std::shared_ptr<MainApplicationWindow> main_window(
        builder->get_widget_derived<MainApplicationWindow>(
            builder,
            "mainWindow",
            network_vm,
            friend_list,
            server_list,
            profile_card,
            home_page,
            direct_msg,
            add_friend,
            add_server));

    return main_window;
}
