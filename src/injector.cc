#include <cstddef>
#include <functional>
#include <gtkmm-4.0/gtkmm.h>

#include "injector.h"

#include "view/MainApplication.h"
#include "view/injector.h"

Glib::RefPtr<Gtk::Application> Injector::inject_app() {
    Glib::RefPtr<MainApplication> view = MainApplication::create();

    GResource* g_res = g_resource_load("./resources.gresource", NULL);
    if (!g_res) {
        return view;
    }

    g_resources_register(g_res);

    using std::placeholders::_1;
    std::function<void(int)> setViewState = std::bind(
        &MainApplication::SetViewState,
        view,
        _1);

    auto login_window = view::Injector::inject_login(setViewState);
    auto main_window = view::Injector::inject_main();

    view->SetViews(
        login_window,
        main_window);

    return view;
}