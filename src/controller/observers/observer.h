#ifndef CONTROLLER_OBSERVERS_OBSERVER_H_
#define CONTROLLER_OBSERVERS_OBSERVER_H_

#include <gtkmm-4.0/gtkmm.h>

class MainApplication;

namespace controller_observers {
class Observer {
 protected:
  Glib::RefPtr<MainApplication> view;

 public:
  virtual void Execute() = 0;
};
}  // namespace controller_observers

#endif