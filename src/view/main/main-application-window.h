#ifndef VIEW_MAIN_APPLICATION_WINDOW_H_
#define VIEW_MAIN_APPLICATION_WINDOW_H_

#include <gtkmm-4.0/gtkmm.h>

#include "view-model/network-view-model.h"

class MainApplicationWindow : public Gtk::ApplicationWindow {
    private:
        std::shared_ptr<view_model::NetworkViewModel> network_vm;
        
        Glib::RefPtr<Gtk::Builder> refBuilder;
        
        Glib::RefPtr<Gtk::Button> send_button;

    public:
        MainApplicationWindow(
            BaseObjectType *cobject,
            const Glib::RefPtr<Gtk::Builder> &refBuilder,
            std::shared_ptr<view_model::NetworkViewModel> network_vm
        );
        virtual ~MainApplicationWindow();
};

#endif