#include "user-message.h"

using namespace chat_client_model_message_functionality;
using namespace chat_client_model_message_functionality_client_stream_out;
using json = nlohmann::json;

UserMessage::UserMessage(const std::string &from, const std::string &content) {
  this->from = from;
  this->content = content;
}

std::string UserMessage::ToString() { return this->ToJson().dump(); }

json UserMessage::ToJson() {
  json json_object = {{"type", "UserMessage"},
                      {"from", this->from},
                      {"content", this->content}};

  return json_object;
}