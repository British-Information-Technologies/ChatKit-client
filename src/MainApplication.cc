#include "MainApplication.h"

#include <stdio.h>

/*
 *
 */
MainApplication::MainApplication()
    : Application("org.gtkmm.examples.application") {
  builder = Builder::create();
  builder->add_from_file("resources/mickyb18-chat-client.glade");

  main_window = builder->get_widget<Gtk::Widget>("main_window");
}

MainApplication::~MainApplication() { this->release(); }

Glib::RefPtr<MainApplication> MainApplication::create() {
  return Glib::make_refptr_for_instance<MainApplication>(new MainApplication());
}

void MainApplication::on_activate() { main_window->show(); }