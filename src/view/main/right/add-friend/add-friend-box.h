#ifndef VIEW_MAIN_RIGHT_ADD_FRIEND_BOX_H_
#define VIEW_MAIN_RIGHT_ADD_FRIEND_BOX_H_

#include "glibmm/refptr.h"
#include "gtkmm/box.h"
#include "gtkmm/builder.h"
#include "gtkmm/button.h"
#include "gtkmm/entry.h"
#include "gtkmm/eventcontrollerkey.h"

#include "view/main/right/add-friend/send-invite-button.h"

class AddFriend : public Gtk::Box {
private:
    const Glib::RefPtr<Gtk::Builder> refBuilder;

    const Glib::RefPtr<Gtk::EventControllerKey> event_ck;

    const Glib::RefPtr<Gtk::Entry> friend_code_entry;

    const Glib::RefPtr<Gtk::Box> add_friend_profile_card_box;

    const Glib::RefPtr<Gtk::Button> send_invite_button;

private:
    bool EnterPressed(guint keyval, guint _, Gdk::ModifierType state);

public:
    AddFriend(
        BaseObjectType* cobject,
        const Glib::RefPtr<Gtk::Builder>& refBuilder,
        const Glib::RefPtr<SendInviteButton> send_invite_button);

    ~AddFriend() = default;
};

#endif