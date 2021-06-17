#ifndef CPPCHATCLIENT_VIEW_GUIVIEW_H_
#define CPPCHATCLIENT_VIEW_GUIVIEW_H_

#include <gtk/gtk.h>
#include <pthread.h>

#include <memory>
#include <string>

#include "../model/friend-functionality/friend-node.h"
#include "../view/view.h"

using namespace std;
using namespace chat_client_model_friend_functionality;

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

  string GetInputUuidToAdd();

  void AddFriendToFriendList(shared_ptr<FriendNode>);

  // void AddObserverAddFriendButton(void (*func)(GtkButton *, gpointer));
  void AddObserverAddFriendButton(Observer &controller);

 protected:
  void InternalThreadEntry();
};
}  // namespace chat_client_view

#endif