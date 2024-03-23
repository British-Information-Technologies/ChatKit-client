#include "message-list-box.h"

#include "glibmm/refptr.h"
#include "gtkmm/box.h"
#include "gtkmm/builder.h"
#include "gtkmm/button.h"

MessageListBox::MessageListBox(
    BaseObjectType* cobject,
    const Glib::RefPtr<Gtk::Builder>& refBuilder,
    const Glib::RefPtr<Gtk::Box> message_box,
    const Glib::RefPtr<Gtk::Button> content_button,
    const Glib::RefPtr<MessageEntry> message_entry)
    : Glib::ObjectBase("MessageListBox"),
      Gtk::Box(cobject),
      refBuilder(refBuilder),
      message_box(message_box),
      content_button(content_button),
      message_entry(message_entry) {}

void MessageListBox::AppendMessageToList(Glib::RefPtr<Gtk::Widget> child) {
    message_box->append(*child);
}