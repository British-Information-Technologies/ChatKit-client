#include <gtkmm-4.0/gtkmm.h>
#include <string>
#include <iostream>

#include "main-application-window.h"

#include "view-model/network-view-model.h"

MainApplicationWindow::MainApplicationWindow(
    BaseObjectType *cobject, 
    const Glib::RefPtr<Gtk::Builder> &refBuilder,
    std::shared_ptr<view_model::NetworkViewModel> network_vm,
    Glib::RefPtr<Gtk::Box> friend_list,
    Glib::RefPtr<Gtk::Box> server_list,
    Glib::RefPtr<Gtk::Box> profile_card,
    Glib::RefPtr<Gtk::Box> home_page,
    Glib::RefPtr<Gtk::Box> direct_msg,
    Glib::RefPtr<Gtk::Box> add_friend
): Glib::ObjectBase("MainApplicationWindow"), Gtk::ApplicationWindow(cobject)
{
    this->network_vm = network_vm;

    this->refBuilder = refBuilder;

    this->refProvider = Gtk::CssProvider::create();

    Gtk::StyleProvider::add_provider_for_display(
        get_display(),
        this->refProvider,
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );

    this->refProvider->signal_parsing_error().connect(
        [](const auto& section, const auto& error) {
            on_parsing_error(section, error);
        }
    );
    
    this->refProvider->load_from_resource("/view/res/panel_style.css");
    
    home_page_button = this->refBuilder->get_object<Gtk::Button>("homepageButton");
    home_page_button->signal_clicked().connect(sigc::mem_fun(
        *this,
        &MainApplicationWindow::SetHomePageState
    ));
    
    friend_list_button = this->refBuilder->get_object<Gtk::Button>("friendListButton");
    friend_list_button->signal_clicked().connect(sigc::mem_fun(
        *this,
        &MainApplicationWindow::SetFriendListState
    ));
    
    server_list_button = this->refBuilder->get_object<Gtk::Button>("serverListButton");
    server_list_button->signal_clicked().connect(sigc::mem_fun(
        *this,
        &MainApplicationWindow::SetServerListState
    ));

    this->friend_list = friend_list;

    this->server_list = server_list;

    this->profile_card = profile_card;

    this->home_page = home_page;

    this->direct_msg = direct_msg;
    
    this->add_friend = add_friend;
}

MainApplicationWindow::~MainApplicationWindow() {}

void MainApplicationWindow::on_parsing_error(
    const Glib::RefPtr<const Gtk::CssSection>& section,
    const Glib::Error& error
) {
  std::cerr << "on_parsing_error(): " << error.what() << std::endl;
  if (section) {
    const auto file = section->get_file();
    if (file) {
      std::cerr << "  URI = " << file->get_uri() << std::endl;
    }

    auto start_location = section->get_start_location();
    auto end_location = section->get_end_location();
    std::cerr << "  start_line = " << start_location.get_lines()+1
              << ", end_line = " << end_location.get_lines()+1 << std::endl;
    std::cerr << "  start_position = " << start_location.get_line_chars()
              << ", end_position = " << end_location.get_line_chars() << std::endl;
  }
}

void MainApplicationWindow::SetHomePageState() {
    direct_msg->hide();
    add_friend->hide();
    home_page->show();
}

void MainApplicationWindow::SetDirectMessageState() {
    add_friend->hide();
    home_page->hide();
    direct_msg->show();
}

void MainApplicationWindow::SetAddFriendState() {
    direct_msg->hide();
    home_page->hide();
    add_friend->show();
}

void MainApplicationWindow::SetFriendListState() {
    server_list->hide();
    friend_list->show();
}

void MainApplicationWindow::SetServerListState() {
    friend_list->hide();
    server_list->show();
}