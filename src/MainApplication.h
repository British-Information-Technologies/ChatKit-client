#ifndef _APPLICATION_H
#define _APPLICATION_H

#include <gtkmm-4.0/gtkmm.h>

/**
 * Author: @michael-bailey
 * # MainApplication
 * This class defines the main application of the client
 * It handles all application level events like activation and opening files
 */
class MainApplication : public Gtk::Application {
 private:
  Glib::RefPtr<Gtk::Builder> builder;
  Gtk::Window* main_window;

 protected:
  MainApplication();
  ~MainApplication();

  void on_activate() override;

 public:
  static Glib::RefPtr<MainApplication> create();
};

#endif