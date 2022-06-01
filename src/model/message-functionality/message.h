#ifndef MODEL_MESSAGE_FUNCTIONALITY_MESSAGE_H_
#define MODEL_MESSAGE_FUNCTIONALITY_MESSAGE_H_

#include <nlohmann/json.hpp>
#include <string>

namespace model_message_functionality {

const std::string INVALID = "Invalid";

class Message {
 public:
  virtual std::string ToString() = 0;
  virtual nlohmann::json ToJson() = 0;
};

}  // namespace model_message_functionality

#endif