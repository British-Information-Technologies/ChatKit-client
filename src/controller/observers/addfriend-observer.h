#ifndef CONTROLLER_OBSERVERS_ADDFRIEND_OBSERVER_H_
#define CONTROLLER_OBSERVERS_ADDFRIEND_OBSERVER_H_

#include "cpp-chat-client/model/client-model.h"
#include "cpp-chat-client/view/MainApplication.h"
#include "cpp-chat-client/controller/observers/observer.h"

namespace controller_observers {
class AddFriendObserver : public Observer {
 private:
  std::shared_ptr<model::ClientModel> model;

 public:
  AddFriendObserver(std::shared_ptr<model::ClientModel>,
                    Glib::RefPtr<MainApplication>);

  void Execute();
};
}  // namespace controller_observers

#endif