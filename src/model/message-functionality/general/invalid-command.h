#ifndef MODEL_MESSAGE_FUNCTIONALITY_GENERAL_INVALID_COMMAND_H_
#define MODEL_MESSAGE_FUNCTIONALITY_GENERAL_INVALID_COMMAND_H_

#include "../message.h"

namespace model_message_functionality_general {
class InvalidCommand : public model_message_functionality::Message {
 public:
  std::string ToString();

  nlohmann::json ToJson();
};

}  // namespace model_message_functionality_general

#endif