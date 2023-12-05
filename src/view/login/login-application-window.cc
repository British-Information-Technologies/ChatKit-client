#include <gtkmm-4.0/gtkmm.h>
#include <memory>

#include "login-application-window.h"

#include "view-model/account-view-model.h"

LoginApplicationWindow::LoginApplicationWindow(
    BaseObjectType* cobject,
    const Glib::RefPtr<Gtk::Builder>& refBuilder,
    std::shared_ptr<view_model::AccountViewModel> account_vm) : Glib::ObjectBase("LoginApplicationWindow"), Gtk::ApplicationWindow(cobject) {
    this->account_vm = account_vm;

    this->refBuilder = refBuilder;

    login_button = this->refBuilder->get_object<Gtk::Button>("loginButton");
    login_button->signal_clicked().connect(sigc::mem_fun(
        *this->account_vm,
        &view_model::AccountViewModel::LoginObserver));
}

LoginApplicationWindow::~LoginApplicationWindow() {}