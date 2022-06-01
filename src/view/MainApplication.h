#ifndef VIEW_MAIN_APPLICATION_H_
#define VIEW_MAIN_APPLICATION_H_

#include <gtkmm-4.0/gtkmm.h>

#include "controller/observers/observer.h"
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
  Gtk::Button* send_button = nullptr;

  Gtk::Entry* message_box = nullptr;

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
  std::string GetInputNameToAdd();
  std::string GetInputUuidToDelete();
  std::string GetMessageBoxText();

  void AddMessageToChatBox(const std::string&, const std::string&);

  void AddFriendToFriendList(
      std::shared_ptr<model_friend_functionality::FriendNode>);
  void RemoveFriendFromFriendList(const std::string&);

  void AddObserverAddFriendButton(controller_observers::Observer&);
  void AddObserverDeleteFriendButton(controller_observers::Observer&);
  void AddObserverSendButton(controller_observers::Observer&);
};

#endif