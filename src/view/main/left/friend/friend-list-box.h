#ifndef VIEW_MAIN_LEFT_FRIEND_LIST_BOX_H_
#define VIEW_MAIN_LEFT_FRIEND_LIST_BOX_H_

#include "glibmm/refptr.h"
#include "gtkmm/box.h"
#include "gtkmm/builder.h"
#include "gtkmm/button.h"
#include "view/main/left/shared/contact-list-box.h"

class FriendListBox : public ContactListBox {
public:
    FriendListBox(
        BaseObjectType* cobject,
        const Glib::RefPtr<Gtk::Builder>& refBuilder,
        const Glib::RefPtr<Gtk::Button> add_friend_button);

    ~FriendListBox() = default;
};

#endif