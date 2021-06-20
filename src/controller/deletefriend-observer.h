#ifndef CPPCHATCLIENT_CONTROLLER_DELETEFRIEND_OBSERVER_H_
#define CPPCHATCLIENT_CONTROLLER_DELETEFRIEND_OBSERVER_H_

#include "../model/client-model.h"
#include "observer.h"

namespace chat_client_controller {
class DeleteFriendObserver : public Observer {
 private:
  std::shared_ptr<chat_client_model::ClientModel> model;

 public:
  DeleteFriendObserver(std::shared_ptr<chat_client_model::ClientModel>,
                       std::shared_ptr<chat_client_view::View>);

  void Execute();
};
}  // namespace chat_client_controller

#endif