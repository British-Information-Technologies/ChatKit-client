#ifndef CPPCHATCLIENT_CONTROLLER_OBSERVER_H_
#define CPPCHATCLIENT_CONTROLLER_OBSERVER_H_

#include <gtkmm-4.0/gtkmm.h>

class MainApplication;

namespace chat_client_view {
class View;
}

namespace chat_client_controller {
class Observer {
 protected:
  Glib::RefPtr<MainApplication> view;

 public:
  virtual void Execute() = 0;
};
}  // namespace chat_client_controller

#endif