#ifndef VIEW_MAIN_APPLICATION_WINDOW_H_
#define VIEW_MAIN_APPLICATION_WINDOW_H_

#include <gtkmm-4.0/gtkmm.h>

#include "view-model/network-view-model.h"

class MainApplicationWindow : public Gtk::ApplicationWindow {
    private:
        std::shared_ptr<view_model::NetworkViewModel> network_vm;
        
        Glib::RefPtr<Gtk::Builder> refBuilder;
        
        Glib::RefPtr<Gtk::CssProvider> refProvider;
        
        Glib::RefPtr<Gtk::Button> home_page_button;
        Glib::RefPtr<Gtk::Button> friend_list_button;
        Glib::RefPtr<Gtk::Button> server_list_button;

        Glib::RefPtr<Gtk::Box> friend_list;
        Glib::RefPtr<Gtk::Box> server_list;
        Glib::RefPtr<Gtk::Box> profile_card;
        Glib::RefPtr<Gtk::Box> home_page;
        Glib::RefPtr<Gtk::Box> direct_msg;
        Glib::RefPtr<Gtk::Box> add_friend;

    public:
        MainApplicationWindow(
            BaseObjectType *cobject,
            const Glib::RefPtr<Gtk::Builder> &refBuilder,
            Glib::RefPtr<Gtk::Box> friend_list,
            Glib::RefPtr<Gtk::Box> server_list,
            Glib::RefPtr<Gtk::Box> profile_card,
            Glib::RefPtr<Gtk::Box> home_page,
            Glib::RefPtr<Gtk::Box> direct_msg,
            Glib::RefPtr<Gtk::Box> add_friend
        );
        virtual ~MainApplicationWindow();

        void SetNetworkViewModel(std::shared_ptr<view_model::NetworkViewModel> network_vm);
        
        void SetHomePageState();
        
        void SetDirectMessageState();

        void SetAddFriendState();
    
        void SetFriendListState();
        
        void SetServerListState();
 
    protected:
        static void on_parsing_error(
            const Glib::RefPtr<const Gtk::CssSection>& section,
            const Glib::Error& error
        );
};

#endif