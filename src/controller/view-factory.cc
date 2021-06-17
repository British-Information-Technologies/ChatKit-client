#include "view-factory.h"

#include "../view/gui-view.h"

using namespace chat_client_controller;
using namespace chat_client_view;

unique_ptr<View> ViewFactory::CreateView(int argc, char **argv) {
  GuiView gui_view(argc, argv);
  gui_view.Setup(argc, argv);

  unique_ptr<View> gui_ptr(new GuiView(move(gui_view)));
  return gui_ptr;
}