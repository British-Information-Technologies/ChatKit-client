#ifndef VIEW_MAIN_RIGHT_DIRECT_MESSAGE_BOX_H_
#define VIEW_MAIN_RIGHT_DIRECT_MESSAGE_BOX_H_

#include "glibmm/refptr.h"
#include "gtkmm/box.h"
#include "gtkmm/builder.h"
#include "gtkmm/button.h"
#include <memory>

#include "gtkmm/scrolledwindow.h"

#include "view/main/right/direct-message/message-entry.h"
#include "view/main/shared/contact-list-box.h"
#include "view/main/shared/list-box.h"
#include "view/main/shared/message-list-box.h"

class DirectMessage : public Gtk::Box, public ListBox {
private:
    Glib::RefPtr<Gtk::Builder> refBuilder;

    Glib::RefPtr<MessageListBox> message_list_box;

    Glib::RefPtr<ContactListBox> contact_list_box;

public:
    DirectMessage(
        BaseObjectType* cobject,
        const Glib::RefPtr<Gtk::Builder>& refBuilder,
        Glib::RefPtr<MessageListBox> message_list_box,
        Glib::RefPtr<ContactListBox> contact_list_box);

    ~DirectMessage() = default;

    void AppendToList(ListType type, const Glib::RefPtr<Gtk::Widget> child);
};

#endif