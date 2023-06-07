#include <gtkmm-4.0/gtkmm.h>

#include "login-application-window.h"

LoginApplicationWindow::LoginApplicationWindow(
    BaseObjectType *cobject, 
    const Glib::RefPtr<Gtk::Builder> &refBuilder
): Glib::ObjectBase("LoginApplicationWindow"), Gtk::ApplicationWindow(cobject)
{}

LoginApplicationWindow::~LoginApplicationWindow() {}