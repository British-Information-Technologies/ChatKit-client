#ifndef CONTROLLER_NETWORKING_CALLBACKS_CALLBACK_COLLECTION_H_
#define CONTROLLER_NETWORKING_CALLBACKS_CALLBACK_COLLECTION_H_

#include <gtkmm-4.0/gtkmm.h>

#include <memory>

#include "cpp-chat-client/model/client-model.h"
#include "cpp-chat-client/model/networking/connection.h"
#include "cpp-chat-client/view/MainApplication.h"

namespace controller_networking_callbacks {

struct CallbackCollection {
  std::shared_ptr<model::ClientModel> model;

  Glib::RefPtr<MainApplication> view;

  std::shared_ptr<model_networking::Connection> connection;
};

}  // namespace controller_networking_callbacks

#endif