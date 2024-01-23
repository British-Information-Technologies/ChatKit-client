#ifndef VIEW_MAIN_LEFT_SERVER_PROFILE_CARD_BUTTON_H_
#define VIEW_MAIN_LEFT_SERVER_PROFILE_CARD_BUTTON_H_

#include <gtkmm-4.0/gtkmm.h>

#include "view-model/network-view-model.h"

class ServerProfileCardButton : public Gtk::Button {
private:
    Glib::RefPtr<Gtk::Builder> refBuilder;
    Glib::RefPtr<Gtk::Label> name_label;
    Glib::RefPtr<Gtk::Label> type_label;

public:
    ServerProfileCardButton(
        BaseObjectType* cobject,
        const Glib::RefPtr<Gtk::Builder>& refBuilder,
        std::shared_ptr<view_model::NetworkViewModel> network_vm,
        const std::string& name,
        const std::string& type);

    virtual ~ServerProfileCardButton();
};

#endif