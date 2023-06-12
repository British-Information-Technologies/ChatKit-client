#include <gtkmm-4.0/gtkmm.h>

#include "login-button.h"

LoginButton::LoginButton(
    BaseObjectType *cobject,
    const Glib::RefPtr<Gtk::Builder> &refBuilder
): Glib::ObjectBase("LoginButton"), Gtk::Button(cobject) {
    this->refBuilder = refBuilder;
}

LoginButton::~LoginButton() {}


void LoginButton::on_clicked() {
    // if login is correct

    auto login_window = refBuilder->get_object<Gtk::ApplicationWindow>("loginWindow");
    auto main_window = refBuilder->get_object<Gtk::ApplicationWindow>("mainWindow");

    login_window->hide();
    main_window->show();
}