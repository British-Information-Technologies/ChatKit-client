#include "ViewFactory.h"
#include "../view/GuiView.h"

using namespace chat_client_controller;

chat_client_view::View * ViewFactory::createView(int argc, char **argv) {
    chat_client_view::GuiView guiView(argc, argv);
    chat_client_view::View *view = guiView.getInstance(argc, argv);

    return view;
}