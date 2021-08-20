#include "info-command.h"

using namespace chat_client_model_message_functionality;
using namespace chat_client_model_message_functionality_network_stream_out;
using json = nlohmann::json;

std::string InfoCommand::ToString() { return this->ToJson().dump(); }

json InfoCommand::ToJson() {
  json json_object = {{"type", "Info"}};

  return json_object;
}