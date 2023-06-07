#include <gtkmm-4.0/gtkmm.h>
#include <functional>

#include "login-application-window.h"

LoginApplicationWindow::LoginApplicationWindow(
    BaseObjectType *cobject, 
    const Glib::RefPtr<Gtk::Builder> &refBuilder,
    std::function<void()> login_func
): Glib::ObjectBase("LoginApplicationWindow"), Gtk::ApplicationWindow(cobject)
{
    login_button = refBuilder->get_object<Gtk::Button>("loginButton");
    login_button->signal_clicked().connect(login_func);
}

LoginApplicationWindow::~LoginApplicationWindow() {}