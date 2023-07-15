#include <functional>
#include <memory>
#include <gtkmm-4.0/gtkmm.h>

#include "injector.h"

#include "view-model/injector.h"
#include "view-model/account-view-model.h"
#include "view-model/network-view-model.h"

#include "login/login-application-window.h"
#include "main/main-application-window.h"

using namespace view;

std::shared_ptr<Gtk::ApplicationWindow> Injector::inject_login(
    std::function<void(int)> setViewState
) {
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create();        
    
    UpdateBuilder(builder, "view/login.ui");

    std::shared_ptr<view_model::AccountViewModel> account_vm = view_model::Injector::inject_account_vm(
        setViewState
    );
            
    /*std::shared_ptr<view_model::AccountViewModel> account_vm(
        new view_model::AccountViewModel(
            setViewState
        )
    );*/

    std::shared_ptr<Gtk::ApplicationWindow> login_window(
        builder->get_widget_derived<LoginApplicationWindow>(
            builder,
            "loginWindow",
            account_vm
        )
    );

    return login_window;
}

std::shared_ptr<Gtk::ApplicationWindow> Injector::inject_main() {
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create();
    
    UpdateBuilder(builder, "view/main.ui");
    
    std::shared_ptr<view_model::NetworkViewModel> network_vm = view_model::Injector::inject_network_vm(
        builder->get_object<Gtk::Entry>("msgEntry")
    );

    /*std::shared_ptr<view_model::NetworkViewModel> network_vm(
        new view_model::NetworkViewModel(
            builder->get_object<Gtk::Entry>("msgEntry")
        )
    );*/
    
    std::shared_ptr<Gtk::ApplicationWindow> main_window(
        builder->get_widget_derived<MainApplicationWindow>(
            builder,
            "mainWindow",
            network_vm
        )
    );
    
    return main_window;
}

int Injector::UpdateBuilder(
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