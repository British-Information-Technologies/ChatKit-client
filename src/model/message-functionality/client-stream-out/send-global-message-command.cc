#include "send-global-message-command.h"

using namespace chat_client_model_message_functionality;
using namespace chat_client_model_message_functionality_client_stream_out;
using json = nlohmann::json;

SendGlobalMessageCommand::SendGlobalMessageCommand(const std::string &content) {
  this->content = content;
}

std::string SendGlobalMessageCommand::ToString() {
  return this->ToJson().dump();
}

json SendGlobalMessageCommand::ToJson() {
  json json_object = {{"type", "SendGlobalMessage"},
                      {"content", this->content}};

  return json_object;
}