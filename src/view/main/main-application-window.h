#ifndef VIEW_MAIN_APPLICATION_WINDOW_H_
#define VIEW_MAIN_APPLICATION_WINDOW_H_

#include <gtkmm-4.0/gtkmm.h>

#include "model/client-model.h"

class MainApplicationWindow : public Gtk::ApplicationWindow {
    private:
        Gtk::Button* send_button = nullptr;

    public:
        MainApplicationWindow(
            BaseObjectType *cobject,
            const Glib::RefPtr<Gtk::Builder> &refBuilder,
            std::shared_ptr<model::ClientModel> model
        );
        virtual ~MainApplicationWindow();
};

#endif