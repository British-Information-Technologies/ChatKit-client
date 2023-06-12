#ifndef VIEW_MAIN_APPLICATION_H_
#define VIEW_MAIN_APPLICATION_H_

#include <gtkmm-4.0/gtkmm.h>
#include <string>
#include <memory>

#include "model/client-model.h"

/**
 * Author: @michael-bailey @Mitch161
 * # MainApplication
 * This class defines the main application of the client
 * It handles all application level events like activation and opening files
 */
class MainApplication : public Gtk::Application {
private:
  Glib::RefPtr<Gtk::Builder> builder = nullptr;

  Gtk::ApplicationWindow *login_window = nullptr;
  Gtk::ApplicationWindow *main_window = nullptr;

protected:
  MainApplication(std::shared_ptr<model::ClientModel> model);
  virtual ~MainApplication();

  // application lifecycle signals
  void on_startup() override;
  void on_activate() override;
  void on_shutdown() override;

public:
  static Glib::RefPtr<MainApplication> create(std::shared_ptr<model::ClientModel> model);

private:
  int UpdateBuilder(const std::string &filename);
};

#endif