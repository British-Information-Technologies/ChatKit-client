#ifndef CPPCHATCLIENT_CONTROLLER_APPLICATION_H_
#define CPPCHATCLIENT_CONTROLLER_APPLICATION_H_

#include <controller/observer.h>

#include "model/friend-functionality/friend-node.h"

/**
 * Author: @michael-bailey
 * # MainApplication
 * This class defines the main application of the client
 * It handles all application level events like activation and opening files
 */
class MainApplication : public Gtk::Application {
 private:
  Glib::RefPtr<Gtk::Builder> builder = nullptr;
  Gtk::Window* main_window = nullptr;
  Gtk::Button* add_friend_button = nullptr;
  Gtk::Button* delete_friend_button = nullptr;

 protected:
  MainApplication();
  ~MainApplication();

  // application lifecycle signals
  void on_startup() override;
  void on_activate() override;
  void on_shutdown() override;

 public:
  static Glib::RefPtr<MainApplication> create();

  std::string GetInputUuidToAdd();
  std::string GetInputUuidToDelete();

  void AddFriendToFriendList(
      std::shared_ptr<chat_client_model_friend_functionality::FriendNode>);
  void RemoveFriendFromFriendList(const std::string&);

  void AddObserverAddFriendButton(chat_client_controller::Observer&);
  void AddObserverDeleteFriendButton(chat_client_controller::Observer&);
};

#endif