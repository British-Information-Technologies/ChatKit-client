#include <gtkmm-4.0/gtkmm.h>
#include <functional>

#include "application-injector.h"

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

Glib::RefPtr<Gtk::Application> ApplicationInjector::inject() {
    Glib::RefPtr<MainApplication> view = MainApplication::create();

    using std::placeholders::_1;
    std::function<void(int)> setViewState = std::bind(
        &MainApplication::SetViewState,
        view,
        _1
    );

    auto login_window = ViewInjector::inject_login(setViewState);
    auto main_window  = ViewInjector::inject_main();

    view->SetViews(
        login_window,
        main_window
    );
    
    return view;
}