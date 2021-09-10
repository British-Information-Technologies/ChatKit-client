#include "disconnected-command.h"

using namespace model_message_functionality;
using namespace model_message_functionality_client_stream_in;
using json = nlohmann::json;

std::string DisconnectedCommand::ToString() { return this->ToJson().dump(); }

json DisconnectedCommand::ToJson() {
  json json_object = {{"type", "Disconnected"}};

  return json_object;
}