#ifndef VIEW_MAIN_APPLICATION_H_
#define VIEW_MAIN_APPLICATION_H_

#include <gtkmm-4.0/gtkmm.h>
#include <string>
#include <memory>

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
  void SetViewState(int state);
  void SetViews(
    std::shared_ptr<Gtk::ApplicationWindow> login_window,
    std::shared_ptr<Gtk::ApplicationWindow> main_window
  );
  
  static Glib::RefPtr<MainApplication> create();

};

#endif