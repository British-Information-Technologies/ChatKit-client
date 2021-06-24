#ifndef CPPCHATCLIENT_VIEW_GUIVIEW_H_
#define CPPCHATCLIENT_VIEW_GUIVIEW_H_

#include <gtkmm-4.0/gtkmm.h>

#include <memory>
#include <string>

#include "../model/friend-functionality/friend-node.h"
#include "../view/view.h"

namespace chat_client_view {
class GuiView : public View {
 private:
  GtkBuilder *builder;
  GtkWidget *window;
  // GMainContext *context;
  int argc;
  char **argv;

 public:
  GuiView(int argc, char **argv);

  void Start();

  void Setup(int, char **);

  void Menu();

  std::string GetInputUuidToAdd();

  std::string GetInputUuidToDelete();

  void AddFriendToFriendList(
      std::shared_ptr<chat_client_model_friend_functionality::FriendNode>);

  void RemoveFriendFromFriendList(const std::string &);

  void AddObserverAddFriendButton(chat_client_controller::Observer &);

  void AddObserverDeleteFriendButton(chat_client_controller::Observer &);
};
}  // namespace chat_client_view

#endif