#ifndef CONTROLLER_NETWORKING_RECEIVER_H_
#define CONTROLLER_NETWORKING_RECEIVER_H_

#include <event2/event.h>

#include <string>
#include <unordered_map>

#include "cpp-chat-client/thread.h"
#include "cpp-chat-client/model/client-model.h"
#include "cpp-chat-client/model/networking/connection.h"
#include "cpp-chat-client/view/MainApplication.h"

namespace controller_networking {

class NetworkReceiver : public thread_wrapper::Thread {
 private:
  std::shared_ptr<model::ClientModel> model;

  Glib::RefPtr<MainApplication> view;

  std::unique_ptr<struct event_base, decltype(&::event_base_free)> base_ptr;

 private:
  void Listen(
      std::unordered_map<int, std::shared_ptr<model_networking::Connection>>
          connections);

  int Stop();

 protected:
  void InternalThreadEntry();

 public:
  NetworkReceiver(std::shared_ptr<model::ClientModel> model,
                  Glib::RefPtr<MainApplication> view);

  ~NetworkReceiver();

  void WaitForInternalThreadToExit();
};

}  // namespace controller_networking

#endif