#include <gtkmm-4.0/gtkmm.h>
#include <string>
#include <memory>
#include <iostream>

#include "MainApplication.h"

MainApplication::MainApplication(): Gtk::Application("org.gtkmm.example") {}

MainApplication::~MainApplication() {}

void MainApplication::on_startup() {
  Gtk::Application::on_startup();
}

void MainApplication::on_activate() {
  Gtk::Application::on_activate();
  add_window(*login_window);
  login_window->show();
}

void MainApplication::on_shutdown() {
  Gtk::Application::on_shutdown();

  if (login_window) {
    login_window->hide();
    remove_window(*login_window);
  }
  
  if (main_window) {
    main_window->hide();
    remove_window(*main_window);
  }
}

void MainApplication::SetViewState(int state) {
  // state = 1 logout
  if (state) {
    add_window(*login_window);
    main_window->hide();
    login_window->show();
    remove_window(*main_window);
    return;
  }

  // state = 0 login
  add_window(*main_window);
  login_window->hide();
  main_window->show();
  remove_window(*login_window);
}

void MainApplication::SetViews(
  std::shared_ptr<Gtk::ApplicationWindow> login_window,
  std::shared_ptr<Gtk::ApplicationWindow> main_window
) {
  this->login_window = login_window;
  this->main_window = main_window;
}

Glib::RefPtr<MainApplication> MainApplication::create() {
  return Glib::make_refptr_for_instance<MainApplication>(
    new MainApplication()
  );
}