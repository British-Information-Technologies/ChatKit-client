#include <gtkmm-4.0/gtkmm.h>

#include "home-application-window.h"

HomeApplicationWindow::HomeApplicationWindow(
    BaseObjectType *cobject, 
    const Glib::RefPtr<Gtk::Builder> &refBuilder
): Glib::ObjectBase("HomeApplicationWindow"), Gtk::ApplicationWindow(cobject)
{}

HomeApplicationWindow::~HomeApplicationWindow() {}