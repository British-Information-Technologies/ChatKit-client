#include "direct-message-box.h"

#include "glibmm/refptr.h"
#include "gtkmm/box.h"
#include "gtkmm/builder.h"
#include "gtkmm/button.h"
#include <memory>

#include "gtkmm/scrollable.h"
#include "view/main/right/direct-message/message-entry.h"
#include "view/main/shared/contact-list-box.h"
#include "view/main/shared/list-box.h"
#include "view/main/shared/message-list-box.h"

DirectMessage::DirectMessage(
    BaseObjectType* cobject,
    const Glib::RefPtr<Gtk::Builder>& refBuilder,
    Glib::RefPtr<MessageListBox> message_list_box,
    Glib::RefPtr<ContactListBox> contact_list_box)
    : Glib::ObjectBase("DirectMessageBox"),
      Gtk::Box(cobject),
      refBuilder(refBuilder),
      message_list_box(message_list_box),
      contact_list_box(contact_list_box) {}

void DirectMessage::AppendToList(ListType type, const Glib::RefPtr<Gtk::Widget> child) {
    // todo make into two overloading functions?
    switch (type) {
    case ListType::Contact:
        contact_list_box->AppendContactToList(child);
        break;
    case ListType::Message:
        message_list_box->AppendMessageToList(child);
    }
}