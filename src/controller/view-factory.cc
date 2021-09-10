#include "view-factory.h"

using namespace controller;
using namespace std;

Glib::RefPtr<MainApplication> ViewFactory::CreateView(int argc, char **argv) {
  auto app = MainApplication::create();

  return app;
}