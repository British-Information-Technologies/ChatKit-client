#include "server-list-box.h"

#include "glibmm/refptr.h"
#include "gtkmm/box.h"
#include "gtkmm/builder.h"
#include "gtkmm/button.h"
#include "view/main/shared/contact-list-box.h"
#include "view/main/shared/list-box.h"

ServerListBox::ServerListBox(
    BaseObjectType* cobject,
    const Glib::RefPtr<Gtk::Builder>& refBuilder,
    const Glib::RefPtr<Gtk::Button> add_server_button,
    const Glib::RefPtr<ContactListBox> contact_list_box)
    : Glib::ObjectBase("ServerListBox"),
      Gtk::Box(cobject),
      ListBox(),
      refBuilder(refBuilder),
      add_server_button(add_server_button),
      contact_list_box(contact_list_box) {}

void ServerListBox::AppendToList(ListType type, const Glib::RefPtr<Gtk::Widget> child) {
    switch (type) {
    case ListType::Contact:
        contact_list_box->AppendContactToList(child);
        break;
    default:
        // todo log error
        break;
    }
}