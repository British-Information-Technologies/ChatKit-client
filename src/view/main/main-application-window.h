#ifndef VIEW_MAIN_APPLICATION_WINDOW_H_
#define VIEW_MAIN_APPLICATION_WINDOW_H_

#include <gtkmm-4.0/gtkmm.h>

#include "glibmm/refptr.h"
#include "gtkmm/box.h"
#include "gtkmm/button.h"
#include "view-model/network-view-model.h"

class MainApplicationWindow : public Gtk::ApplicationWindow {
private:
    std::shared_ptr<view_model::NetworkViewModel> network_vm;

    const Glib::RefPtr<Gtk::Builder> refBuilder;

    Glib::RefPtr<Gtk::CssProvider> refProvider;

    const Glib::RefPtr<Gtk::Button> home_page_button;
    const Glib::RefPtr<Gtk::Button> friend_list_button;
    const Glib::RefPtr<Gtk::Button> server_list_button;

    const Glib::RefPtr<Gtk::Box> left_pane;
    const Glib::RefPtr<Gtk::Box> right_pane;
    const Glib::RefPtr<Gtk::Box> friend_list;
    const Glib::RefPtr<Gtk::Box> server_list;
    const Glib::RefPtr<Gtk::Box> profile_card;
    const Glib::RefPtr<Gtk::Box> home_page;
    const Glib::RefPtr<Gtk::Box> direct_msg;
    const Glib::RefPtr<Gtk::Box> add_friend;
    const Glib::RefPtr<Gtk::Box> add_server;

public:
    MainApplicationWindow(
        BaseObjectType* cobject,
        const Glib::RefPtr<Gtk::Builder>& refBuilder,
        std::shared_ptr<view_model::NetworkViewModel> network_vm,
        const Glib::RefPtr<Gtk::Box> left_pane,
        const Glib::RefPtr<Gtk::Box> right_pane,
        Gtk::Box* friend_list,
        Gtk::Box* server_list,
        Gtk::Box* profile_card,
        Gtk::Box* home_page,
        Gtk::Box* direct_msg,
        Gtk::Box* add_friend,
        Gtk::Box* add_server);

    virtual ~MainApplicationWindow();

    void SetHomePageState();

    void SetFriendListState();

    void SetServerListState();

protected:
    static void on_parsing_error(
        const Glib::RefPtr<const Gtk::CssSection>& section,
        const Glib::Error& error);
};

#endif