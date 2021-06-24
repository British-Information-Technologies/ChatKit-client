#ifndef _APPLICATION_H
#define _APPLICATION_H

#include <gtkmm-4.0/gtkmm.h>

#include "main-window.h"

using namespace chat_client_view;
using namespace Gtk;

/**
 * Author: @michael-bailey
 * # MainApplication
 * This class defines the main application of the client
 * It handles all application level events like activation and opening files
 */
class MainApplication : public Application {
 private:
  Glib::RefPtr<Gtk::Builder> builder;
  Gtk::Widget *main_window;

 protected:
  MainApplication();
  ~MainApplication();

  void on_activate() override;

 public:
  static Glib::RefPtr<MainApplication> create();
};

#endif