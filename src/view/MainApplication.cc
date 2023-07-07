#include <gtkmm-4.0/gtkmm.h>
#include <string>
#include <memory>
#include <iostream>
#include <functional>

#include "MainApplication.h"

#include "login/login-application-window.h"
#include "main/main-application-window.h"

namespace {
  class ViewInjector {
    public:
      static std::shared_ptr<Gtk::ApplicationWindow> inject_login(
        std::function<void(int)> setViewState
      ) {
        Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create();
        
        UpdateBuilder(builder, "view/login.ui");
      
        std::shared_ptr<view_model::AccountViewModel> account_vm(
          new view_model::AccountViewModel(
            setViewState
          )
        );
    
        std::shared_ptr<Gtk::ApplicationWindow> login_window(
          builder->get_widget_derived<LoginApplicationWindow>(
            builder,
            "loginWindow",
            account_vm
          )
        );

        return login_window;
      }

      static std::shared_ptr<Gtk::ApplicationWindow> inject_main() {
        Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create();
        
        UpdateBuilder(builder, "view/main.ui");
        
        std::shared_ptr<view_model::NetworkViewModel> network_vm(
          new view_model::NetworkViewModel(
            builder->get_object<Gtk::Entry>("msgEntry")
          )
        );

        std::shared_ptr<Gtk::ApplicationWindow> main_window(
          builder->get_widget_derived<MainApplicationWindow>(
            builder,
            "mainWindow",
            network_vm
          )
        );

        return main_window;
      }

    private:
      static int UpdateBuilder(
        const Glib::RefPtr<Gtk::Builder> &ref_builder,
        const std::string &filename
      ) {
        try {
          if (!ref_builder->add_from_file(filename)) {
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
  };
} // namespace


MainApplication::MainApplication(): Gtk::Application("org.gtkmm.example") {
  auto setViewState = [this](int state) {
    // state = 1 logout
    if (state) {
      this->main_window->hide();
      this->login_window->show();
      return;
    }

    // state = 0 login
    this->login_window->hide();
    this->main_window->show();
  };
  
  login_window = ViewInjector::inject_login(setViewState);
  main_window  = ViewInjector::inject_main();
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
  return Glib::make_refptr_for_instance<MainApplication>(
    new MainApplication()
  );
}

/*void MainApplication::SetViewState(int state) {
  printf("Lambda Function, State = %d\n", state);

  /*
  // state = 1 logout
  if (state) {
    this->main_window->hide();
    this->login_window->show();
    return;
  }

  // state = 0 login
  this->login_window->hide();
  this->main_window->show();
  */
//}