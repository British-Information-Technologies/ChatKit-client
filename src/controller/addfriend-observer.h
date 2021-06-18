#ifndef CPPCHATCLIENT_CONTROLLER_ADDFRIEND_OBSERVER_H_
#define CPPCHATCLIENT_CONTROLLER_ADDFRIEND_OBSERVER_H_

#include "../model/client-model.h"
#include "observer.h"

namespace chat_client_controller {
class AddFriendObserver : public Observer {
 private:
  std::shared_ptr<chat_client_model::ClientModel> model;

 public:
  AddFriendObserver(std::shared_ptr<chat_client_model::ClientModel>,
                    std::shared_ptr<chat_client_view::View>);

  void Execute();
};
}  // namespace chat_client_controller

#endif