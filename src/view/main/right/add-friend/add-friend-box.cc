#include "add-friend-box.h"

#include "glibmm/refptr.h"
#include "gtkmm/box.h"
#include "gtkmm/builder.h"
#include "gtkmm/button.h"
#include "gtkmm/entry.h"
#include "gtkmm/eventcontrollerkey.h"

#include "view/main/right/add-friend/send-invite-button.h"

AddFriend::AddFriend(
    BaseObjectType* cobject,
    const Glib::RefPtr<Gtk::Builder>& refBuilder,
    Glib::RefPtr<SendInviteButton> send_invite_button)
    : Glib::ObjectBase("AddFriend"),
      Gtk::Box(cobject),
      refBuilder(refBuilder),
      friend_code_entry(refBuilder->get_object<Gtk::Entry>("friendCodeEntry")),
      add_friend_profile_card_box(refBuilder->get_object<Gtk::Box>("addFriendProfileCardBox")),
      send_invite_button(send_invite_button),
      event_ck(Gtk::EventControllerKey::create()) {
    event_ck->signal_key_pressed().connect(
        sigc::mem_fun(*this, &AddFriend::EnterPressed),
        false);

    add_controller(event_ck);
}

// TODO (eventually remove): faked for testing reasons
bool AddFriend::EnterPressed(guint keyval, guint _, Gdk::ModifierType state) {
    if (keyval == GDK_KEY_Return) {
        add_friend_profile_card_box->show();
    }

    return false;
}
