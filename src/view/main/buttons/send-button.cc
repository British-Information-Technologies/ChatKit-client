#include <gtkmm-4.0/gtkmm.h>
#include <string>

#include "send-button.h"

#include "model/client-model.h"

SendButton::SendButton(
    BaseObjectType *cobject,
    const Glib::RefPtr<Gtk::Builder> &refBuilder,
    std::shared_ptr<model::ClientModel> model
): Glib::ObjectBase("SendButton"), Gtk::Button(cobject) {
    this->refBuilder = refBuilder;
    this->model = model;
}

SendButton::~SendButton() {}


void SendButton::on_clicked() {
    auto msg_entry = refBuilder->get_object<Gtk::Entry>("msgEntry");
        
    if (msg_entry->get_text_length() == 0) {
        return;
    }

    printf("Message to send: %s\n", msg_entry->get_text().c_str());
}