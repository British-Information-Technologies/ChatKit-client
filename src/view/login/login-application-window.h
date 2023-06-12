#ifndef VIEW_LOGIN_APPLICATION_WINDOW_H_
#define VIEW_LOGIN_APPLICATION_WINDOW_H_

#include <gtkmm-4.0/gtkmm.h>
#include <functional>

#include "buttons/login-button.h"

class LoginApplicationWindow : public Gtk::ApplicationWindow {
    private:
        Gtk::Button* login_button = nullptr;

    public:
        LoginApplicationWindow(
            BaseObjectType *cobject,
            const Glib::RefPtr<Gtk::Builder> &refBuilder
        );
        virtual ~LoginApplicationWindow();
};

#endif