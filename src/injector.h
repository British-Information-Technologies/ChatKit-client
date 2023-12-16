#ifndef APPLICATION_INJECTOR_H_
#define APPLICATION_INJECTOR_H_

#include <gtkmm-4.0/gtkmm.h>

class Injector {
public:
    static Glib::RefPtr<Gtk::Application> inject_app();
};

#endif