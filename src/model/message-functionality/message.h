#ifndef MODEL_MESSAGEFUNCTIONALITY_MESSAGE_H_
#define MODEL_MESSAGEFUNCTIONALITY_MESSAGE_H_

#include <nlohmann/json.hpp>
#include <string>

namespace chat_client_model_message_functionality {

const std::string INVALID = "Invalid";

class Message {
 public:
  virtual std::string ToString() = 0;
  virtual nlohmann::json ToJson() = 0;
};

}  // namespace chat_client_model_message_functionality

#endif