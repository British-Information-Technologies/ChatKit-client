#include "send-message.h"

using namespace chat_client_model_message_functionality;
using namespace chat_client_model_message_functionality_client_stream_in;
using json = nlohmann::json;

SendMessage::SendMessage(const std::string &to, const std::string &content) {
  this->to = to;
  this->content = content;
}

std::string SendMessage::ToString() { return this->ToJson().dump(); }

json SendMessage::ToJson() {
  json json_object = {
      {"type", "SendMessage"}, {"to", this->to}, {"content", this->content}};

  return json_object;
}