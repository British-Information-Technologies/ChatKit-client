#include "contact-list-box.h"

#include "glibmm/refptr.h"
#include "gtkmm/box.h"
#include "gtkmm/builder.h"
#include "gtkmm/button.h"

ContactListBox::ContactListBox(
    BaseObjectType* cobject,
    const std::string& name,
    const Glib::RefPtr<Gtk::Builder>& refBuilder,
    const Glib::RefPtr<Gtk::Button> add_contact_button,
    const Glib::RefPtr<Gtk::Box> contact_box)
    : Glib::ObjectBase(name.c_str()),
      Gtk::Box(cobject),
      refBuilder(refBuilder),
      add_contact_button(add_contact_button),
      contact_box(contact_box) {}

void ContactListBox::AppendContactToList(Glib::RefPtr<Gtk::Widget> child) {
    contact_box->append(*child);
}