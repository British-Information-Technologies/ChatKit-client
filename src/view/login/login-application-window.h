#ifndef VIEW_LOGIN_APPLICATION_WINDOW_H_
#define VIEW_LOGIN_APPLICATION_WINDOW_H_

#include <gtkmm-4.0/gtkmm.h>
#include <memory>

#include "view-model/account-view-model.h"

class LoginApplicationWindow : public Gtk::ApplicationWindow {
    private:
        std::shared_ptr<view_model::AccountViewModel> account_vm;
        
        Glib::RefPtr<Gtk::Builder> refBuilder;
        
        Glib::RefPtr<Gtk::Button> login_button;

    public:
        LoginApplicationWindow(
            BaseObjectType *cobject,
            const Glib::RefPtr<Gtk::Builder> &refBuilder,
            std::shared_ptr<view_model::AccountViewModel> account_vm
        );
        virtual ~LoginApplicationWindow();
};

#endif