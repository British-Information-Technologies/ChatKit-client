#include "global-message.h"

using namespace chat_client_model_message_functionality;
using namespace chat_client_model_message_functionality_client_stream_out;
using json = nlohmann::json;

GlobalMessage::GlobalMessage(const std::string &content) {
  this->content = content;
}

std::string GlobalMessage::ToString() { return this->ToJson().dump(); }

json GlobalMessage::ToJson() {
  json json_object = {{"type", "GlobalMessage"}, {"content", this->content}};

  return json_object;
}