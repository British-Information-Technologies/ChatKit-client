#ifndef CPPCHATCLIENT_CONTROLLER_VIEWFACTORY_H_
#define CPPCHATCLIENT_CONTROLLER_VIEWFACTORY_H_

#include <memory>

#include "../view/MainApplication.h"

namespace chat_client_controller {
class ViewFactory {
 public:
  Glib::RefPtr<MainApplication> CreateView(int, char **);
};
}  // namespace chat_client_controller

#endif