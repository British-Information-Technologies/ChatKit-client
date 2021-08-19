#include "user-message-command.h"

using namespace chat_client_model_message_functionality;
using namespace chat_client_model_message_functionality_client_stream_in;
using json = nlohmann::json;

UserMessageCommand::UserMessageCommand(const std::string &from,
                                       const std::string &content) {
  this->from = from;
  this->content = content;
}

std::string UserMessageCommand::ToString() { return this->ToJson().dump(); }

json UserMessageCommand::ToJson() {
  json json_object = {{"type", "UserMessage"},
                      {"from", this->from},
                      {"content", this->content}};

  return json_object;
}