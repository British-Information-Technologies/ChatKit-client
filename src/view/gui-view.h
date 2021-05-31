#ifndef CPPCHATCLIENT_VIEW_GUIVIEW_H_
#define CPPCHATCLIENT_VIEW_GUIVIEW_H_

#include <pthread.h>

#include "../view/view.h"

namespace chat_client_view {
class GuiView : View {
 private:
  GuiView *instance;
  bool initalised;
  int argc;
  char **argv;

  void Start();

 public:
  GuiView(int argc, char **argv);

  void Menu();

  View *GetInstance(int, char **);

 protected:
  void InternalThreadEntry();
};
}  // namespace chat_client_view

#endif