#include "ViewFactory.h"
#include "../view/GuiView.h"

using namespace chat_client_controller;
using namespace chat_client_view;

View * ViewFactory::createView(int argc, char **argv) {
    GuiView guiView(argc, argv);
    View *view = guiView.getInstance(argc, argv);

    return view;
}