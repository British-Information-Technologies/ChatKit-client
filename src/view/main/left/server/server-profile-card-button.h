#ifndef VIEW_MAIN_LEFT_SERVER_PROFILE_CARD_BUTTON_H_
#define VIEW_MAIN_LEFT_SERVER_PROFILE_CARD_BUTTON_H_

#include "glibmm/refptr.h"
#include "gtkmm/builder.h"
#include "gtkmm/button.h"
#include "gtkmm/label.h"
#include <memory>
#include <string>

#include "view-model/network-view-model.h"
#include "view/observers/notifications/notification-observer.h"

class ServerProfileCardButton : public Gtk::Button {
private:
    Glib::RefPtr<Gtk::Builder> refBuilder;

    std::shared_ptr<view_model::NetworkViewModel> network_vm;

    Glib::RefPtr<Gtk::Label> name_label;
    Glib::RefPtr<Gtk::Label> owner_label;

    view::NotificationObserver* notification;

    std::string ip_address;
    std::string port;

protected:
    void on_clicked() override;

public:
    ServerProfileCardButton(
        BaseObjectType* cobject,
        const Glib::RefPtr<Gtk::Builder>& refBuilder,
        std::shared_ptr<view_model::NetworkViewModel> network_vm,
        const std::string& name,
        const std::string& owner,
        view::NotificationObserver* notification,
        const std::string& ip_address,
        const std::string& port);

    virtual ~ServerProfileCardButton();
};

#endif