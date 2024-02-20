#ifndef VIEW_MAIN_RIGHT_DIRECT_MESSAGE_BOX_H_
#define VIEW_MAIN_RIGHT_DIRECT_MESSAGE_BOX_H_

#include "glibmm/refptr.h"
#include "gtkmm/box.h"
#include "gtkmm/builder.h"
#include "gtkmm/button.h"
#include <memory>

#include "view/main/right/direct-message/message-entry.h"

class DirectMessage : public Gtk::Box {
private:
    const Glib::RefPtr<Gtk::Builder> refBuilder;

    const Glib::RefPtr<Gtk::Button> content_button;

    const Glib::RefPtr<MessageEntry> message_entry;

public:
    DirectMessage(
        BaseObjectType* cobject,
        const Glib::RefPtr<Gtk::Builder>& refBuilder,
        Glib::RefPtr<MessageEntry> message_entry);

    ~DirectMessage() = default;
};

#endif