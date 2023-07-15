#include <gtkmm-4.0/gtkmm.h>
#include <functional>

#include "injector.h"

#include "view/MainApplication.h"
#include "view/injector.h"

Glib::RefPtr<Gtk::Application> Injector::inject_app() { 
    Glib::RefPtr<MainApplication> view = MainApplication::create();

    using std::placeholders::_1;
    std::function<void(int)> setViewState = std::bind(
        &MainApplication::SetViewState,
        view,
        _1
    );

    auto login_window = view::Injector::inject_login(setViewState);
    auto main_window  = view::Injector::inject_main();
    
    view->SetViews(
        login_window,
        main_window
    );
    
    return view;
}