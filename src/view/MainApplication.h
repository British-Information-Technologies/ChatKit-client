#ifndef VIEW_MAIN_APPLICATION_H_
#define VIEW_MAIN_APPLICATION_H_

#include <gtkmm-4.0/gtkmm.h>
#include <string>
#include <memory>

#include "view-model/network-view-model.h"
#include "view-model/account-view-model.h"

/**
 * Author: @michael-bailey @Mitch161
 * # MainApplication
 * This class defines the main application of the client
 * It handles all application level events like activation and opening files
 */
class MainApplication : public Gtk::Application {
private:
  std::shared_ptr<Gtk::ApplicationWindow> login_window;
  std::shared_ptr<Gtk::ApplicationWindow> main_window;

protected:
  MainApplication();
  virtual ~MainApplication();

  // application lifecycle signals
  void on_startup() override;
  void on_activate() override;
  void on_shutdown() override;

public:
  static Glib::RefPtr<MainApplication> create();

//private:
  //void SetViewState(int state);
};

#endif