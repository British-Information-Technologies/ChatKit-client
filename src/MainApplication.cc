#include "MainApplication.h"

using namespace Gtk;

MainApplication::MainApplication()
    : Application("org.gtkmm.examples.application") { this->hold(); }

MainApplication::~MainApplication() { this->release(); }

Glib::RefPtr<MainApplication> MainApplication::create() {
  return Glib::make_refptr_for_instance<MainApplication>(new MainApplication());
}

void MainApplication::on_startup() {
	Application::on_startup();

	builder = Builder::create_from_file("resources/mickyb18-chat-client.glade");
  main_window = builder->get_widget<Window>("main_window");
}

void MainApplication::on_activate() {
	Application::on_activate();
	
  add_window(*main_window);
  main_window->show();
}

void MainApplication::on_shutdown() {
	Application::on_shutdown();

	main_window->hide();
	remove_window(*main_window);
}