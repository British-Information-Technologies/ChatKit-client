#ifndef MODEL_MESSAGEFUNCTIONALITY_MESSAGE_
#define MODEL_MESSAGEFUNCTIONALITY_MESSAGE_

#include <nlohmann/json.hpp>
#include <string>

namespace chat_client_model_message_functionality {
class Message {
 public:
  virtual std::string ToString() = 0;
  virtual nlohmann::json ToJson() = 0;
};
}  // namespace chat_client_model_message_functionality

#endif