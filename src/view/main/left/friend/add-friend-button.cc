#include "add-friend-button.h"

#include "gtkmm/builder.h"
#include "gtkmm/button.h"

#include "view/observers/notifications/notification-observer.h"

AddFriendButton::AddFriendButton(
    BaseObjectType* cobject,
    const Glib::RefPtr<Gtk::Builder>& refBuilder,
    view::NotificationObserver* show_add_friend)
    : Glib::ObjectBase("AddFriendButton"),
      Gtk::Button(cobject),
      refBuilder(refBuilder),
      show_add_friend(show_add_friend) {}

void AddFriendButton::on_clicked() {
    show_add_friend->Notify("todo F1", "todo F2");
}