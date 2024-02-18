#include "direct-message-box.h"

#include "glibmm/refptr.h"
#include "gtkmm/box.h"
#include "gtkmm/builder.h"
#include "gtkmm/button.h"
#include <memory>

#include "view/main/right/direct-message/message-entry.h"

DirectMessage::DirectMessage(
    BaseObjectType* cobject,
    const Glib::RefPtr<Gtk::Builder>& refBuilder,
    Glib::RefPtr<MessageEntry> message_entry)
    : Glib::ObjectBase("DirectMessage"),
      Gtk::Box(cobject),
      refBuilder(refBuilder),
      content_button(refBuilder->get_object<Gtk::Button>("contentButton")),
      message_entry(message_entry) {}