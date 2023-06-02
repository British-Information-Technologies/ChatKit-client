#include <iostream>

#include "MainApplication.h"

#include "controller/observers/observer.h"

using namespace Gtk;
using namespace controller_observers;
using namespace model_friend_functionality;

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

std::string MainApplication::GetInputNameToAdd() {return "filter text"; }

std::string MainApplication::GetInputUuidToDelete() { return "filler text"; }

std::string MainApplication::GetMessageBoxText() {
  return message_box->get_text();
}

void MainApplication::AddMessageToChatBox(const std::string &message,
                                          const std::string &uuid) {
  Gtk::Stack *chat_box = builder->get_widget<Gtk::Stack>(uuid + "_stack");

  Gtk::Text text;
  text.set_text(message);

  chat_box->add(text);
}

void MainApplication::AddFriendToFriendList(
    std::shared_ptr<FriendNode> friend_node) {
  std::cout << "added" << std::endl;
}

void MainApplication::RemoveFriendFromFriendList(const std::string &uuid) {
  std::cout << "removed" << std::endl;
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