#ifndef VIEW_MAIN_RIGHT_ADD_SERVER_JOIN_BUTTON_H_
#define VIEW_MAIN_RIGHT_ADD_SERVER_JOIN_BUTTON_H_

#include "glibmm/refptr.h"
#include "gtkmm/builder.h"
#include "gtkmm/button.h"
#include "gtkmm/label.h"
#include <memory>

#include "view-model/network-view-model.h"
#include "view/observers/notifications/notification-observer.h"
#include "view/observers/notifications/vbox-notification-observer.h"
#include "view/observers/server-observables.h"

class JoinButton : public Gtk::Button {
private:
    const Glib::RefPtr<Gtk::Builder> refBuilder;

    Glib::RefPtr<Gtk::Label> server_name_label;

    Glib::RefPtr<Gtk::Label> server_owner_label;

    std::shared_ptr<view_model::NetworkViewModel> network_vm;

    std::unique_ptr<view::VboxNotificationObserver> append_contact;

    std::unique_ptr<view::ServerObservables> observables;

    char* ip_address;
    char* port;

protected:
    void on_clicked() override;

public:
    JoinButton(
        BaseObjectType* cobject,
        const Glib::RefPtr<Gtk::Builder>& refBuilder,
        char* ip_address,
        char* port,
        view::VboxNotificationObserver* append_contact,
        view::ServerObservables* observables,
        std::shared_ptr<view_model::NetworkViewModel> network_vm);

    ~JoinButton() = default;
};

#endif