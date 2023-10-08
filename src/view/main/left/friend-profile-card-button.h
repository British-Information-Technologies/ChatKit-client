#ifndef VIEW_MAIN_LEFT_FRIEND_PROFILE_CARD_BUTTON_H_
#define VIEW_MAIN_LEFT_FRIEND_PROFILE_CARD_BUTTON_H_

#include <gtkmm-4.0/gtkmm.h>

#include "view-model/network-view-model.h"

class FriendProfileCardButton : public Gtk::Button {
    private:
        Glib::RefPtr<Gtk::Builder> refBuilder;
        Glib::RefPtr<Gtk::Label> username_label;
        Glib::RefPtr<Gtk::Label> chat_type_label;

    public:
        FriendProfileCardButton(
            BaseObjectType *cobject,
            const Glib::RefPtr<Gtk::Builder> &refBuilder,
            std::shared_ptr<view_model::NetworkViewModel> network_vm,
            const std::string &username,
            const std::string &type
        );
        virtual ~FriendProfileCardButton();        
};

#endif