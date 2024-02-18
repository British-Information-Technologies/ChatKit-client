#ifndef VIEW_MAIN_RIGHT_ADD_FRIEND_SEND_INVITE_BUTTON_H_
#define VIEW_MAIN_RIGHT_ADD_FRIEND_SEND_INVITE_BUTTON_H_

#include "glibmm/refptr.h"
#include "gtkmm/button.h"
#include <memory>

#include "view-model/network-view-model.h"
#include "view/observers/notifications/notification-observer.h"
#include "view/observers/notifications/vbox-notification-observer.h"

class SendInviteButton : public Gtk::Button {
private:
    const Glib::RefPtr<Gtk::Builder>& refBuilder;

    std::shared_ptr<view_model::NetworkViewModel> network_vm;

    std::unique_ptr<view::VboxNotificationObserver> append_contact;

    std::unique_ptr<view::NotificationObserver> open_contents;

protected:
    void on_clicked() override;

public:
    SendInviteButton(
        BaseObjectType* cobject,
        const Glib::RefPtr<Gtk::Builder>& refBuilder,
        view::VboxNotificationObserver* append_contact,
        view::NotificationObserver* open_contents,
        std::shared_ptr<view_model::NetworkViewModel> network_vm);

    ~SendInviteButton() = default;
};

#endif
