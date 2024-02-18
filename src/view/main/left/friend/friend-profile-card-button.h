#ifndef VIEW_MAIN_LEFT_FRIEND_PROFILE_CARD_BUTTON_H_
#define VIEW_MAIN_LEFT_FRIEND_PROFILE_CARD_BUTTON_H_

#include "glibmm/refptr.h"
#include "gtkmm/builder.h"
#include "gtkmm/button.h"
#include "gtkmm/label.h"
#include <memory>
#include <string>

#include "view-model/network-view-model.h"
#include "view/observers/notifications/notification-observer.h"

class FriendProfileCardButton : public Gtk::Button {
private:
    Glib::RefPtr<Gtk::Builder> refBuilder;

    std::shared_ptr<view_model::NetworkViewModel> network_vm;

    Glib::RefPtr<Gtk::Label> username_label;
    Glib::RefPtr<Gtk::Label> chat_type_label;

    view::NotificationObserver* notification;

protected:
    void on_clicked() override;

public:
    FriendProfileCardButton(
        BaseObjectType* cobject,
        const Glib::RefPtr<Gtk::Builder>& refBuilder,
        std::shared_ptr<view_model::NetworkViewModel> network_vm,
        view::NotificationObserver* notification,
        const std::string& username,
        const std::string& type);
    virtual ~FriendProfileCardButton();
};

#endif