#include "message-entry.h"

#include "gtkmm/entry.h"
#include "gtkmm/eventcontrollerkey.h"
#include <memory>

#include "view-model/network-view-model.h"
#include "view/observers/workers/worker-observer.h"

MessageEntry::MessageEntry(
    BaseObjectType* cobject,
    const Glib::RefPtr<Gtk::Builder>& refBuilder,
    view::WorkerObserver* send_message)
    : Glib::ObjectBase("MessageEntry"),
      Gtk::Entry(cobject),
      send_message(send_message),
      event_ck(Gtk::EventControllerKey::create()) {
    event_ck->signal_key_pressed().connect(
        sigc::mem_fun(*this, &MessageEntry::EnterPressed),
        false);

    add_controller(event_ck);
}

bool MessageEntry::EnterPressed(guint keyval, guint _, Gdk::ModifierType state) {
    if (keyval == GDK_KEY_Return) {
        std::string data(get_text());

        send_message->Execute(data);
    }

    return false;
}