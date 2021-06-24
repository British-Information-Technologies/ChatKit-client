#include "MainApplication.h"

#include <stdio.h>

/*
 *
 */
MainApplication::MainApplication() : Application("org.gtkmm.examples.application") {
  // auto builder = Builder::create();
  // builder->add_from_file("resources/mickyb18-chat-client.glade");
  // this->mainWindow = builder->get_widget<Window>("main_window");


  // this->mainWindow->show();
}

MainApplication::~MainApplication() { this->release(); }

Glib::RefPtr<MainApplication> MainApplication::create() {
	return Glib::make_refptr_for_instance<MainApplication>(new MainApplication());
}