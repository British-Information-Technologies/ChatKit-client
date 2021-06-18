#ifndef CPPCHATCLIENT_VIEW_GUIVIEW_H_
#define CPPCHATCLIENT_VIEW_GUIVIEW_H_

#include <gtk/gtk.h>

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

  void Start();

 public:
  GuiView(int argc, char **argv);

  void Setup(int, char **);

  void Menu();

  std::string GetInputUuidToAdd();

  void AddFriendToFriendList(
      std::shared_ptr<chat_client_model_friend_functionality::FriendNode>);

  void AddObserverAddFriendButton(chat_client_controller::Observer &);

 protected:
  void InternalThreadEntry();
};
}  // namespace chat_client_view

#endif