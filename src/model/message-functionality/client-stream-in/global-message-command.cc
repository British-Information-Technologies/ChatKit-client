#include "global-message-command.h"

using namespace model_message_functionality;
using namespace model_message_functionality_client_stream_in;
using json = nlohmann::json;

GlobalMessageCommand::GlobalMessageCommand(const std::string &content) {
  this->content = content;
}

std::string GlobalMessageCommand::ToString() { return this->ToJson().dump(); }

json GlobalMessageCommand::ToJson() {
  json json_object = {{"type", "GlobalMessage"}, {"content", this->content}};

  return json_object;
}