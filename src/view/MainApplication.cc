#include <gtkmm-4.0/gtkmm.h>
#include <string>
#include <iostream>

#include "MainApplication.h"

#include "login/login-application-window.h"
#include "home/home-application-window.h"

MainApplication::MainApplication()
    : Gtk::Application("org.gtkmm.example") {
  this->hold();
}

MainApplication::~MainApplication() { this->release(); }

void MainApplication::on_startup() {
  Gtk::Application::on_startup();
}

void MainApplication::on_activate() {
  printf("T1");

  Gtk::Application::on_activate();
  
  printf("T2");

  builder = Gtk::Builder::create();
  
  printf("T3");

  if(SetLoginWindow()) {
    return;
  }
}

void MainApplication::on_shutdown() {
  Gtk::Application::on_shutdown();

  if (app_window) {
    app_window->hide();
    remove_window(*app_window);
  }
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

int MainApplication::SetLoginWindow() {
  if (UpdateBuilder("view/login.ui")) {
    return -1;
  }

  if (app_window) {
    app_window->hide();
    remove_window(*app_window);
  }

  app_window = builder->get_widget_derived<LoginApplicationWindow>(
    builder,
    "rootAppWindow",
    [this](){ Login(); }
  );

  add_window(*app_window);
  app_window->show();

  return 0;
}

int MainApplication::Login() {
  if (UpdateBuilder("view/home.ui")) {
    return -1;
  }

  if (app_window) {
    app_window->hide();
    remove_window(*app_window);
  }

  app_window = builder->get_widget_derived<HomeApplicationWindow>(builder, "rootAppWindow");

  add_window(*app_window);
  app_window->show();

  return 0;
}

Glib::RefPtr<MainApplication> MainApplication::create() {
  return Glib::make_refptr_for_instance<MainApplication>(new MainApplication());
}