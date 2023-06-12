#include <gtkmm-4.0/gtkmm.h>
#include <string>

#include "main-application-window.h"

MainApplicationWindow::MainApplicationWindow(
    BaseObjectType *cobject, 
    const Glib::RefPtr<Gtk::Builder> &refBuilder
): Glib::ObjectBase("MainApplicationWindow"), Gtk::ApplicationWindow(cobject)
{
    send_button = refBuilder->get_object<Gtk::Button>("sendButton");
    send_button->signal_clicked().connect([this](){
        if (msg_entry->get_text_length() == 0) {
            return;
        }

        printf("Message to send: %s\n", msg_entry->get_text());

        /* TODO
        *  Need to send the msg to the model.
        *  Not sure on best approach yet
        */
    });

    msg_entry = refBuilder->get_object<Gtk::Entry>("msgEntry");
}

MainApplicationWindow::~MainApplicationWindow() {}