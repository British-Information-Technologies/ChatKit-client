#include <gtkmm-4.0/gtkmm.h>

#include "view/MainApplication.h"

int main(int argc, char **argv) {
  auto view = MainApplication::create();
  view->run();
}