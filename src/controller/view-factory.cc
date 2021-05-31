#include "view-factory.h"

#include "../view/gui-view.h"

using namespace chat_client_controller;
using namespace chat_client_view;

View *ViewFactory::CreateView(int argc, char **argv) {
  GuiView guiView(argc, argv);
  View *view = guiView.GetInstance(argc, argv);

  return view;
}