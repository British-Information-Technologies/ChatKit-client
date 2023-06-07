#ifndef VIEW_HOME_APPLICATION_WINDOW_H_
#define VIEW_HOME_APPLICATION_WINDOW_H_

#include <gtkmm-4.0/gtkmm.h>

class HomeApplicationWindow : public Gtk::ApplicationWindow {
    public:
        HomeApplicationWindow(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &refBuilder);
        virtual ~HomeApplicationWindow();
};

#endif