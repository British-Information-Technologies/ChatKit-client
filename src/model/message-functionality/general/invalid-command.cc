#include "invalid-command.h"

using namespace chat_client_model_message_functionality;
using namespace chat_client_model_message_functionality_general;
using json = nlohmann::json;

std::string InvalidCommand::ToString() { return this->ToJson().dump(); }

json InvalidCommand::ToJson() {
  json json_object = {{"type", "Invalid"}};
  return json_object;
}