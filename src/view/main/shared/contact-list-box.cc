#include "contact-list-box.h"

#include "glibmm/refptr.h"
#include "gtkmm/box.h"
#include "gtkmm/builder.h"
#include "gtkmm/button.h"

ContactListBox::ContactListBox(
    BaseObjectType* cobject,
    const Glib::RefPtr<Gtk::Builder>& refBuilder,
    const Glib::RefPtr<Gtk::Box> contact_box)
    : Glib::ObjectBase("ContactListBox"),
      Gtk::ScrolledWindow(cobject),
      refBuilder(refBuilder),
      contact_box(contact_box) {}

void ContactListBox::AppendContactToList(Glib::RefPtr<Gtk::Widget> child) {
    contact_box->append(*child);
}