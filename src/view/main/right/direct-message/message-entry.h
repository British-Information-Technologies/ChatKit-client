#ifndef VIEW_MAIN_RIGHT_DIRECT_MESSAGE_ENTRY_H_
#define VIEW_MAIN_RIGHT_DIRECT_MESSAGE_ENTRY_H_

#include "glibmm/refptr.h"
#include "gtkmm/builder.h"
#include "gtkmm/entry.h"
#include "gtkmm/eventcontrollerkey.h"
#include <memory>

#include "view-model/network-view-model.h"
#include "view/observers/workers/worker-observer.h"

class MessageEntry : public Gtk::Entry {
private:
    const Glib::RefPtr<Gtk::Builder> refBuilder;

    std::unique_ptr<view::WorkerObserver> send_message;

    const Glib::RefPtr<Gtk::EventControllerKey> event_ck;

private:
    bool EnterPressed(guint keyval, guint _, Gdk::ModifierType state);

public:
    MessageEntry(
        BaseObjectType* cobject,
        const Glib::RefPtr<Gtk::Builder>& refBuilder,
        view::WorkerObserver* send_message);

    ~MessageEntry() = default;
};

#endif