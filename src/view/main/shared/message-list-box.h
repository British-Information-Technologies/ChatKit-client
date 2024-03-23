#ifndef VIEW_MAIN_SHARED_MESSAGE_LIST_BOX_H_
#define VIEW_MAIN_SHARED_MESSAGE_LIST_BOX_H_

#include "glibmm/refptr.h"
#include "gtkmm/box.h"
#include "gtkmm/builder.h"
#include "gtkmm/button.h"
#include "view/main/right/direct-message/message-entry.h"

class MessageListBox : public Gtk::Box {
protected:
    const Glib::RefPtr<Gtk::Builder> refBuilder;

    const Glib::RefPtr<Gtk::Box> message_box;

    const Glib::RefPtr<Gtk::Button> content_button;

    const Glib::RefPtr<MessageEntry> message_entry;

public:
    MessageListBox(
        BaseObjectType* cobject,
        const Glib::RefPtr<Gtk::Builder>& refBuilder,
        const Glib::RefPtr<Gtk::Box> message_box,
        const Glib::RefPtr<Gtk::Button> content_button,
        const Glib::RefPtr<MessageEntry> message_entry);

    ~MessageListBox() = default;

    void AppendMessageToList(Glib::RefPtr<Gtk::Widget> child);
};

#endif