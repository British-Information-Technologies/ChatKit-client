#include <gtkmm-4.0/gtkmm.h>
#include <functional>

#include "friend-profile-card-button.h"

void FriendProfileCardButton::on_clicked() {
    this->setDirectMessageState();
}

FriendProfileCardButton::FriendProfileCardButton(
    BaseObjectType *cobject, 
    const Glib::RefPtr<Gtk::Builder> &refBuilder,
    std::function<void()> setDirectMessageState
): Glib::ObjectBase("FriendProfileCardButton"), Gtk::Button(cobject)
{
    this->refBuilder = refBuilder;
    this->setDirectMessageState = setDirectMessageState;
}

FriendProfileCardButton::~FriendProfileCardButton() {}