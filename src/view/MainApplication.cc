#include <gtkmm-4.0/gtkmm.h>
#include <string>
#include <iostream>

#include "MainApplication.h"

#include "login/login-application-window.h"
#include "main/main-application-window.h"

MainApplication::MainApplication()
    : Gtk::Application("org.gtkmm.example") {
  builder = Gtk::Builder::create();
  
  UpdateBuilder("view/login.ui");
  UpdateBuilder("view/main.ui");

  login_window = builder->get_widget_derived<LoginApplicationWindow>(
    builder,
    "loginWindow"
  );

  main_window = builder->get_widget_derived<MainApplicationWindow>(
    builder,
    "mainWindow"
  );
}

MainApplication::~MainApplication() {}

void MainApplication::on_startup() {
  Gtk::Application::on_startup();
}

void MainApplication::on_activate() {
  Gtk::Application::on_activate();

  add_window(*login_window);
  add_window(*main_window);

  login_window->show();
  main_window->hide();
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
  
Glib::RefPtr<MainApplication> MainApplication::create() {
  return Glib::make_refptr_for_instance<MainApplication>(new MainApplication());
}

int MainApplication::UpdateBuilder(const std::string &filename) {
  try {
    if (!builder->add_from_file(filename)) {
     printf("Builder failed to add_from_file\n");
     return -1;
    }

  } catch (const Glib::FileError &ex) {
    printf("FileError: %s\n", ex.what());
    return -1;

  } catch (const Glib::MarkupError &ex) {
    printf("MarkupError: %s\n", ex.what());
    return -1;

  } catch (const Gtk::BuilderError &ex) {
    printf("BuilderError: %s\n", ex.what());
    return -1;

  }

  return 0;
}