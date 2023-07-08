#include <gtkmm-4.0/gtkmm.h>

#include "view/application-injector.h"

int main(int argc, char **argv) {
  Glib::RefPtr<Gtk::Application> view = ApplicationInjector::inject();
  view->run();
}