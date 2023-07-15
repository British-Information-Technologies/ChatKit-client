#include <gtkmm-4.0/gtkmm.h>

#include "injector.h"

int main(int argc, char **argv) {
  Glib::RefPtr<Gtk::Application> view = Injector::inject_app();
  view->run();
}