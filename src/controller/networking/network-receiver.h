#ifndef CONTROLLER_NETWORKING_RECEIVER_H_
#define CONTROLLER_NETWORKING_RECEIVER_H_

#include <string>
#include <unordered_map>

#include "../../model/client-model.h"
#include "../../model/networking/connection.h"
#include "../../view/MainApplication.h"

namespace controller_networking {

class NetworkReceiver {
 private:
  std::shared_ptr<model::ClientModel> model;

  Glib::RefPtr<MainApplication> view;

  std::shared_ptr<
      std::unordered_map<int, std::shared_ptr<model_networking::Connection>>>
      connections;

 public:
  NetworkReceiver(std::shared_ptr<model::ClientModel> model,
                  Glib::RefPtr<MainApplication> view,
                  std::shared_ptr<std::unordered_map<
                      int, std::shared_ptr<model_networking::Connection>>>
                      connections);

  ~NetworkReceiver();

  void listen();
};

}  // namespace controller_networking

#endif