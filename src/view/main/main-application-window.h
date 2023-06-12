#ifndef VIEW_MAIN_APPLICATION_WINDOW_H_
#define VIEW_MAIN_APPLICATION_WINDOW_H_

#include <gtkmm-4.0/gtkmm.h>

class MainApplicationWindow : public Gtk::ApplicationWindow {
    private:
        std::shared_ptr<Gtk::Button> send_button;
        std::shared_ptr<Gtk::Entry> msg_entry;

    public:
        MainApplicationWindow(
            BaseObjectType *cobject,
            const Glib::RefPtr<Gtk::Builder> &refBuilder
        );
        virtual ~MainApplicationWindow();
};

#endif