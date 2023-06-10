#ifndef VIEW_MAIN_APPLICATION_H_
#define VIEW_MAIN_APPLICATION_H_

#include <gtkmm-4.0/gtkmm.h>
#include <string>

#include "model/friend-functionality/friend-node.h"

/**
 * Author: @michael-bailey @Mitch161
 * # MainApplication
 * This class defines the main application of the client
 * It handles all application level events like activation and opening files
 */
class MainApplication : public Gtk::Application {
private:
  Glib::RefPtr<Gtk::Builder> builder = nullptr;

  Gtk::ApplicationWindow *app_window = nullptr;

protected:
  MainApplication();
  ~MainApplication();

  // application lifecycle signals
  void on_startup() override;
  void on_activate() override;
  void on_shutdown() override;

public:
  static Glib::RefPtr<MainApplication> create();

private:
  int UpdateBuilder(const std::string &filename);
  
  int SetLoginWindow();
  
  int Login();
};

#endif