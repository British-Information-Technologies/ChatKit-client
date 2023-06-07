#ifndef VIEW_HOME_APPLICATION_WINDOW_H_
#define VIEW_HOME_APPLICATION_WINDOW_H_

#include <gtkmm-4.0/gtkmm.h>

class HomeApplicationWindow : public Gtk::ApplicationWindow {
    private:
        std::shared_ptr<Gtk::Button> send_button;
        std::shared_ptr<Gtk::Entry> msg_entry;

    public:
        HomeApplicationWindow(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &refBuilder);
        virtual ~HomeApplicationWindow();
};

#endif