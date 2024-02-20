#include <gtkmm-4.0/gtkmm.h>
#include <iostream>
#include <string>

#include "main-application-window.h"

#include "view-model/network-view-model.h"

MainApplicationWindow::MainApplicationWindow(
    BaseObjectType* cobject,
    const Glib::RefPtr<Gtk::Builder>& refBuilder,
    std::shared_ptr<view_model::NetworkViewModel> network_vm,
    const Glib::RefPtr<Gtk::Box> left_pane,
    const Glib::RefPtr<Gtk::Box> right_pane,
    const Glib::RefPtr<Gtk::Box> friend_list,
    const Glib::RefPtr<Gtk::Box> server_list,
    const Glib::RefPtr<Gtk::Box> profile_card,
    const Glib::RefPtr<Gtk::Box> home_page,
    const Glib::RefPtr<Gtk::Box> direct_msg,
    const Glib::RefPtr<Gtk::Box> add_friend,
    const Glib::RefPtr<Gtk::Box> add_server)
    : Glib::ObjectBase("MainApplicationWindow"),
      Gtk::ApplicationWindow(cobject),
      refBuilder(refBuilder),
      network_vm(network_vm),
      left_pane(left_pane),
      right_pane(right_pane),
      friend_list(friend_list),
      server_list(server_list),
      profile_card(profile_card),
      home_page(home_page),
      direct_msg(direct_msg),
      add_friend(add_friend),
      add_server(add_server),
      home_page_button(this->refBuilder->get_object<Gtk::Button>("homepageButton")),
      friend_list_button(this->refBuilder->get_object<Gtk::Button>("friendListButton")),
      server_list_button(this->refBuilder->get_object<Gtk::Button>("serverListButton")) {
    this->refProvider = Gtk::CssProvider::create();

    Gtk::StyleProvider::add_provider_for_display(
        get_display(),
        this->refProvider,
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    this->refProvider->signal_parsing_error().connect(
        [](const auto& section, const auto& error) {
            on_parsing_error(section, error);
        });

    this->refProvider->load_from_resource("/view/res/panel_style.css");

    home_page_button->signal_clicked().connect(sigc::mem_fun(
        *this,
        &MainApplicationWindow::SetHomePageState));

    friend_list_button->signal_clicked().connect(sigc::mem_fun(
        *this,
        &MainApplicationWindow::SetFriendListState));

    server_list_button->signal_clicked().connect(sigc::mem_fun(
        *this,
        &MainApplicationWindow::SetServerListState));
}

MainApplicationWindow::~MainApplicationWindow() {}

void MainApplicationWindow::on_parsing_error(
    const Glib::RefPtr<const Gtk::CssSection>& section,
    const Glib::Error& error) {
    std::cerr << "on_parsing_error(): " << error.what() << std::endl;
    if (section) {
        const auto file = section->get_file();
        if (file) {
            std::cerr << "  URI = " << file->get_uri() << std::endl;
        }

        auto start_location = section->get_start_location();
        auto end_location = section->get_end_location();
        std::cerr << "  start_line = " << start_location.get_lines() + 1
                  << ", end_line = " << end_location.get_lines() + 1 << std::endl;
        std::cerr << "  start_position = " << start_location.get_line_chars()
                  << ", end_position = " << end_location.get_line_chars() << std::endl;
    }
}

void MainApplicationWindow::SetHomePageState() {
    direct_msg->hide();
    add_friend->hide();
    add_server->hide();
    home_page->show();
}

void MainApplicationWindow::SetFriendListState() {
    server_list->hide();
    friend_list->show();
}

void MainApplicationWindow::SetServerListState() {
    friend_list->hide();
    server_list->show();
}