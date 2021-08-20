#include "connecting-command.h"

using namespace chat_client_model_message_functionality;
using namespace chat_client_model_message_functionality_network_stream_in;
using json = nlohmann::json;

std::string ConnectingCommand::ToString() { return this->ToJson().dump(); }

json ConnectingCommand::ToJson() {
  json json_object = {{"type", "Connecting"}};

  return json_object;
}