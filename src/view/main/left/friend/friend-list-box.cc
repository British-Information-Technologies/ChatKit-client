#include "friend-list-box.h"

#include "glibmm/refptr.h"
#include "gtkmm/box.h"
#include "gtkmm/builder.h"
#include "gtkmm/button.h"
#include "gtkmm/widget.h"
#include "view/main/shared/contact-list-box.h"
#include "view/main/shared/list-box.h"

FriendListBox::FriendListBox(
    BaseObjectType* cobject,
    const Glib::RefPtr<Gtk::Builder>& refBuilder,
    const Glib::RefPtr<Gtk::Button> add_friend_button,
    const Glib::RefPtr<ContactListBox> contact_list_box)
    : Glib::ObjectBase("FriendListBox"),
      Gtk::Box(cobject),
      ListBox(),
      refBuilder(refBuilder),
      add_friend_button(add_friend_button),
      contact_list_box(contact_list_box) {}

void FriendListBox::AppendToList(ListType type, const Glib::RefPtr<Gtk::Widget> child) {
    switch (type) {
    case ListType::Contact:
        contact_list_box->AppendContactToList(child);
        break;
    default:
        // todo log error
        break;
    }
}