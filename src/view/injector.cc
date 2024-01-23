#include <functional>
#include <gtkmm-4.0/gtkmm.h>
#include <iostream>
#include <memory>

#include "injector.h"

#include "sigc++/functors/mem_fun.h"
#include "view-model/account-view-model.h"
#include "view-model/injector.h"
#include "view-model/network-view-model.h"

#include "view/login/login-application-window.h"

#include "view/main/main-application-window.h"

#include "view/main/left/friend-list-box.h"
#include "view/main/left/friend-profile-card-button.h"
#include "view/main/left/profile-card-box.h"
#include "view/main/left/server-list-box.h"
#include "view/main/left/server-profile-card-button.h"

#include "view/main/right/add-friend-box.h"
#include "view/main/right/add-server-box.h"
#include "view/main/right/direct-message-box.h"
#include "view/main/right/home-page-box.h"

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
    // ensure custom types have been registered with the type system
    g_type_ensure(ADD_FRIEND_TYPE);
    g_type_ensure(ADD_SERVER_TYPE);
    g_type_ensure(DIRECT_MESSAGE_TYPE);
    g_type_ensure(FRIEND_LIST_TYPE);
    g_type_ensure(SERVER_LIST_TYPE);
    g_type_ensure(PROFILE_CARD_TYPE);
    g_type_ensure(HOME_PAGE_TYPE);

    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create();

    UpdateBuilder(builder, "/view/res/main.ui");

    // get templates for main window
    Glib::RefPtr<Gtk::Box> friend_list = builder->get_object<Gtk::Box>("friendListBox");

    Glib::RefPtr<Gtk::Box> server_list = builder->get_object<Gtk::Box>("serverListBox");

    Glib::RefPtr<Gtk::Box> profile_card = builder->get_object<Gtk::Box>("profileCardBox");

    Glib::RefPtr<Gtk::Box> home_page = builder->get_object<Gtk::Box>("homepageBox");

    Glib::RefPtr<Gtk::Box> direct_msg = builder->get_object<Gtk::Box>("directMessageBox");

    Glib::RefPtr<Gtk::Box> add_friend = builder->get_object<Gtk::Box>("addFriendBox");

    Glib::RefPtr<Gtk::Box> add_server = builder->get_object<Gtk::Box>("addServerBox");

    // create main window
    std::shared_ptr<MainApplicationWindow> main_window(
        builder->get_widget_derived<MainApplicationWindow>(
            builder,
            "mainWindow",
            friend_list,
            server_list,
            profile_card,
            home_page,
            direct_msg,
            add_friend,
            add_server));

    // create network view model
    std::shared_ptr<view_model::NetworkViewModel> network_vm = view_model::Injector::inject_network_vm(
        sigc::mem_fun(
            *main_window,
            &MainApplicationWindow::SetDirectMessageState));

    main_window->SetNetworkViewModel(network_vm);

    // assign friend list button behaviour
    set_add_friend_button(sigc::mem_fun(
        *main_window,
        &MainApplicationWindow::SetAddFriendState));

    // assign server list button behaviour
    set_add_server_button(sigc::mem_fun(
        *main_window,
        &MainApplicationWindow::SetAddServerState));

    // TODO: currently hard coded and faked, eventually change with net vm
    set_send_invite_button([network_vm]() {
        auto profile_card_button = Injector::inject_friend_profile_card(
            network_vm,
            "faked uuid");

        append_friend_to_list(profile_card_button);
    });

    set_join_button([network_vm]() {
        auto profile_card_button = Injector::inject_server_profile_card(network_vm);

        append_server_to_list(profile_card_button);
    });

    set_server_code_entry(network_vm);

    set_message_entry(sigc::mem_fun(
        *network_vm,
        &view_model::NetworkViewModel::SendMessageObserver));

    return main_window;
}

std::shared_ptr<Gtk::Button> Injector::inject_friend_profile_card(
    std::shared_ptr<view_model::NetworkViewModel> network_vm,
    const std::string& uuid) {
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create();

    UpdateBuilder(builder, "/view/res/friend_profile_card.ui");

    // TODO: use uuid to load user data from local storage (names, etc)
    const std::string username = "fake username";
    const std::string type = "fake type";

    std::shared_ptr<FriendProfileCardButton> profile_card_button(
        builder->get_widget_derived<FriendProfileCardButton>(
            builder,
            "openChatButton",
            network_vm,
            username,
            type));

    return profile_card_button;
}

std::shared_ptr<Gtk::Button> Injector::inject_server_profile_card(
    std::shared_ptr<view_model::NetworkViewModel> network_vm) {
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create();

    UpdateBuilder(builder, "/view/res/server_profile_card.ui");

    // TODO: use uuid to load user data from local storage (names, etc)
    const std::string server_name = "fake server name";
    const std::string server_type = "fake type";

    std::shared_ptr<ServerProfileCardButton> profile_card_button(
        builder->get_widget_derived<ServerProfileCardButton>(
            builder,
            "openServerButton",
            network_vm,
            server_name,
            server_type));

    return profile_card_button;
}

int Injector::UpdateBuilder(
    const Glib::RefPtr<Gtk::Builder>& ref_builder,
    const std::string& filename) {
    try {
        if (!ref_builder->add_from_resource(filename)) {
            printf("Builder failed to add_from_file\n");
            return -1;
        }

    } catch (const Glib::FileError& ex) {
        printf("FileError: %s\n", ex.what());
        return -1;

    } catch (const Glib::MarkupError& ex) {
        printf("MarkupError: %s\n", ex.what());
        return -1;

    } catch (const Gtk::BuilderError& ex) {
        printf("BuilderError: %s\n", ex.what());
        return -1;
    }

    return 0;
}