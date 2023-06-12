#include <gtkmm-4.0/gtkmm.h>
#include <string>

#include "main-application-window.h"

#include "model/client-model.h"
#include "buttons/send-button.h"

MainApplicationWindow::MainApplicationWindow(
    BaseObjectType *cobject, 
    const Glib::RefPtr<Gtk::Builder> &refBuilder,
    std::shared_ptr<model::ClientModel> model
): Glib::ObjectBase("MainApplicationWindow"), Gtk::ApplicationWindow(cobject)
{
    send_button = refBuilder->get_widget_derived<SendButton>(
        refBuilder,
        "sendButton",
        model
    );
}

MainApplicationWindow::~MainApplicationWindow() {}