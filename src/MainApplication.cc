#include "MainApplication.h"

using namespace Gtk;

/*
 *
 */
MainApplication::MainApplication()
    : Application("org.gtkmm.examples.application") {
  builder = Builder::create_from_file("resources/mickyb18-chat-client.glade");

  main_window = builder->get_widget<Window>("main_window");
}

MainApplication::~MainApplication() { this->release(); }

Glib::RefPtr<MainApplication> MainApplication::create() {
  return Glib::make_refptr_for_instance<MainApplication>(new MainApplication());
}

void MainApplication::on_activate() {
  add_window(*main_window);

  main_window->show();
}