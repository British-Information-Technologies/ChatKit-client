#include "disconnect-command.h"

using namespace chat_client_model_message_functionality;
using namespace chat_client_model_message_functionality_client_stream_out;
using json = nlohmann::json;

std::string DisconnectCommand::ToString() { return this->ToJson().dump(); }

json DisconnectCommand::ToJson() {
  json json_object = {{"type", "Disconnect"}};

  return json_object;
}