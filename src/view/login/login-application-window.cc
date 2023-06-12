#include <gtkmm-4.0/gtkmm.h>
#include <functional>

#include "login-application-window.h"

#include "buttons/login-button.h"

LoginApplicationWindow::LoginApplicationWindow(
    BaseObjectType *cobject, 
    const Glib::RefPtr<Gtk::Builder> &refBuilder
): Glib::ObjectBase("LoginApplicationWindow"), Gtk::ApplicationWindow(cobject)
{
    login_button = refBuilder->get_widget_derived<LoginButton>(
        refBuilder,
        "loginButton"
    );
}

LoginApplicationWindow::~LoginApplicationWindow() {}