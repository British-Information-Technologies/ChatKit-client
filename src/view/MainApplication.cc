#include "MainApplication.h"

#include <iostream>

#include "controller/observers/deletefriend-observer.h"

using namespace Gtk;
using namespace chat_client_controller;
using namespace std;

MainApplication::MainApplication()
    : Application("org.gtkmm.examples.application") {
  this->hold();
}

MainApplication::~MainApplication() { this->release(); }

Glib::RefPtr<MainApplication> MainApplication::create() {
  return Glib::make_refptr_for_instance<MainApplication>(new MainApplication());
}

void MainApplication::on_startup() {
  Application::on_startup();

  builder = Builder::create_from_file("resources/mickyb18-chat-client.glade");
  main_window = builder->get_widget<Window>("main_window");

  add_friend_button = builder->get_widget<Gtk::Button>("add_friend_button");

  delete_friend_button =
      builder->get_widget<Gtk::Button>("delete_friend_button");

  send_button = builder->get_widget<Gtk::Button>("send_button");

  message_box = builder->get_widget<Gtk::Entry>("message_box");
}

void MainApplication::on_activate() {
  Application::on_activate();

  add_window(*main_window);
  main_window->show();
}

void MainApplication::on_shutdown() {
  Application::on_shutdown();

  main_window->hide();
  remove_window(*main_window);
}

std::string MainApplication::GetInputUuidToAdd() { return "filler text"; }

std::string MainApplication::GetInputUuidToDelete() { return "filler text"; }

std::string MainApplication::GetMessageBoxText() {
  return message_box->get_text();
}

void MainApplication::AddFriendToFriendList(
    shared_ptr<FriendNode> friend_node) {
  cout << "added" << endl;
}

void MainApplication::RemoveFriendFromFriendList(const std::string &uuid) {
  cout << "removed" << endl;
}

void MainApplication::AddObserverAddFriendButton(Observer &observer) {
  add_friend_button->signal_clicked().connect(
      sigc::mem_fun(observer, &Observer::Execute));
}

void MainApplication::AddObserverDeleteFriendButton(Observer &observer) {
  delete_friend_button->signal_clicked().connect(
      sigc::mem_fun(observer, &Observer::Execute));
}

void MainApplication::AddObserverSendButton(Observer &observer) {
  send_button->signal_clicked().connect(
      sigc::mem_fun(observer, &Observer::Execute));
}