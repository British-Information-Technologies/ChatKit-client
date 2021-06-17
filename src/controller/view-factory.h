#ifndef CPPCHATCLIENT_CONTROLLER_VIEWFACTORY_H_
#define CPPCHATCLIENT_CONTROLLER_VIEWFACTORY_H_

#include "../view/gui-view.h"

using namespace chat_client_view;

namespace chat_client_controller {
class ViewFactory {
 public:
  unique_ptr<View> CreateView(int, char **);
};
}  // namespace chat_client_controller

#endif