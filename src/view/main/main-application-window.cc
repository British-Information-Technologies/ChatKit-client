#include <gtkmm-4.0/gtkmm.h>
#include <string>

#include "main-application-window.h"

#include "view-model/network-view-model.h"

MainApplicationWindow::MainApplicationWindow(
    BaseObjectType *cobject, 
    const Glib::RefPtr<Gtk::Builder> &refBuilder,
    std::shared_ptr<view_model::NetworkViewModel> network_vm
): Glib::ObjectBase("MainApplicationWindow"), Gtk::ApplicationWindow(cobject)
{
    this->network_vm = network_vm;

    this->refBuilder = refBuilder;

    send_button = this->refBuilder->get_object<Gtk::Button>("sendButton");
    send_button->signal_clicked().connect(sigc::mem_fun(
        *this->network_vm,
        &view_model::NetworkViewModel::SendMessageObserver
    ));
}

MainApplicationWindow::~MainApplicationWindow() {}