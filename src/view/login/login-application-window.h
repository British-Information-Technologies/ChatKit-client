#ifndef VIEW_LOGIN_APPLICATION_WINDOW_H_
#define VIEW_LOGIN_APPLICATION_WINDOW_H_

#include <gtkmm-4.0/gtkmm.h>

class LoginApplicationWindow : public Gtk::ApplicationWindow {
    public:
        LoginApplicationWindow(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &refBuilder);
        virtual ~LoginApplicationWindow();
};

#endif