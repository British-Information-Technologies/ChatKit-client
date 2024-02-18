#include "friend-list-box.h"

#include "glibmm/refptr.h"
#include "gtkmm/box.h"
#include "gtkmm/builder.h"
#include "gtkmm/button.h"
#include "gtkmm/widget.h"
#include "view/main/left/shared/contact-list-box.h"

FriendListBox::FriendListBox(
    BaseObjectType* cobject,
    const Glib::RefPtr<Gtk::Builder>& refBuilder,
    const Glib::RefPtr<Gtk::Button> add_friend_button)
    : ContactListBox(
        cobject,
        "FriendListBox",
        refBuilder,
        add_friend_button,
        refBuilder->get_object<Gtk::Box>("contactBox")) {}