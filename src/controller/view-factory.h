#ifndef CPPCHATCLIENT_CONTROLLER_VIEWFACTORY_H_
#define CPPCHATCLIENT_CONTROLLER_VIEWFACTORY_H_

#include <memory>

#include "../view/view.h"

namespace chat_client_controller {
class ViewFactory {
 public:
  std::shared_ptr<chat_client_view::View> CreateView(int, char **);
};
}  // namespace chat_client_controller

#endif