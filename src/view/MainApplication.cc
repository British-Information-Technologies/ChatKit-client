#include <gtkmm-4.0/gtkmm.h>
#include <iostream>

#include "MainApplication.h"

MainApplication::MainApplication()
    : Gtk::Application("org.gtkmm.example") {
  this->hold();
}

MainApplication::~MainApplication() { this->release(); }

void MainApplication::on_startup() {
  Gtk::Application::on_startup();
}

void MainApplication::on_activate() {
  Gtk::Application::on_activate();

  builder = Gtk::Builder::create();

  try {
    if (!builder->add_from_file("view/login.ui")) {
     printf("Builder failed to add_from_file\n");
     return;
    }

  } catch (const Glib::FileError &ex) {
    printf("FileError: %s\n", ex.what());
    return;

  } catch (const Glib::MarkupError &ex) {
    printf("MarkupError: %s\n", ex.what());
    return;

  } catch (const Gtk::BuilderError &ex) {
    printf("BuilderError: %s\n", ex.what());
    return;

  }

  app_window = builder->get_widget<Gtk::ApplicationWindow>("rootAppWindow");

  add_window(*app_window);
  app_window->show();
}

void MainApplication::on_shutdown() {
  Gtk::Application::on_shutdown();

  app_window->hide();
  remove_window(*app_window);
}

Glib::RefPtr<MainApplication> MainApplication::create() {
  return Glib::make_refptr_for_instance<MainApplication>(new MainApplication());
}