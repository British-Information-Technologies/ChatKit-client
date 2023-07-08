#ifndef VIEW_INJECTORS_APPLICATION_H_
#define VIEW_INJECTORS_APPLICATION_H_

#include <gtkmm-4.0/gtkmm.h>

class ApplicationInjector {
    public:
        static Glib::RefPtr<Gtk::Application> inject();
};

#endif