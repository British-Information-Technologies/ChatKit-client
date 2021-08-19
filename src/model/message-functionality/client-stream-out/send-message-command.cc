#include "send-message-command.h"

using namespace chat_client_model_message_functionality;
using namespace chat_client_model_message_functionality_client_stream_out;
using json = nlohmann::json;

SendMessageCommand::SendMessageCommand(const std::string &to,
                                       const std::string &content) {
  this->to = to;
  this->content = content;
}

std::string SendMessageCommand::ToString() { return this->ToJson().dump(); }

json SendMessageCommand::ToJson() {
  json json_object = {
      {"type", "SendMessage"}, {"to", this->to}, {"content", this->content}};

  return json_object;
}