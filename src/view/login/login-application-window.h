#ifndef VIEW_LOGIN_APPLICATION_WINDOW_H_
#define VIEW_LOGIN_APPLICATION_WINDOW_H_

#include <gtkmm-4.0/gtkmm.h>
#include <functional>

class LoginApplicationWindow : public Gtk::ApplicationWindow {
    private:
        std::shared_ptr<Gtk::Button> login_button;

    public:
        LoginApplicationWindow(
            BaseObjectType *cobject,
            const Glib::RefPtr<Gtk::Builder> &refBuilder,
            std::function<void()> login_func
        );
        virtual ~LoginApplicationWindow();
};

#endif