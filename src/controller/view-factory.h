#ifndef CONTROLLER_VIEW_FACTORY_H_
#define CONTROLLER_VIEW_FACTORY_H_

#include <memory>

#include "../view/MainApplication.h"

namespace controller {
class ViewFactory {
 public:
  Glib::RefPtr<MainApplication> CreateView(int, char **);
};
}  // namespace controller

#endif