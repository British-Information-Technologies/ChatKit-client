#ifndef VIEW_MAIN_RIGHT_ADD_SERVER_BOX_H_
#define VIEW_MAIN_RIGHT_ADD_SERVER_BOX_H_

#include "glibmm/refptr.h"
#include "gtkmm/box.h"
#include "gtkmm/builder.h"
#include "gtkmm/entry.h"
#include "gtkmm/eventcontrollerkey.h"
#include "gtkmm/label.h"
#include <memory>

#include "view-model/network-view-model.h"
#include "view/main/right/add-server/join-button.h"
#include "view/observers/notifications/notification-observer.h"

class AddServer : public Gtk::Box {
private:
    const Glib::RefPtr<Gtk::Builder> refBuilder;

    const Glib::RefPtr<Gtk::EventControllerKey> event_ck;

    const Glib::RefPtr<Gtk::Entry> server_code_entry;

    const Glib::RefPtr<Gtk::Box> add_server_profile_card_box;

    const Glib::RefPtr<Gtk::Label> server_name_label;

    const Glib::RefPtr<Gtk::Label> server_owner_label;

    const Glib::RefPtr<JoinButton> join_button;

    std::shared_ptr<view_model::NetworkViewModel> network_vm;

    std::unique_ptr<view::ServerObservables> observables;

    char* ip_address;
    char* port;

private:
    bool EnterPressed(guint keyval, guint _, Gdk::ModifierType state);

public:
    AddServer(
        BaseObjectType* cobject,
        const Glib::RefPtr<Gtk::Builder>& refBuilder,
        char* ip_address,
        char* port,
        const Glib::RefPtr<JoinButton> join_button,
        std::shared_ptr<view_model::NetworkViewModel> network_vm);

    ~AddServer();
};

#endif