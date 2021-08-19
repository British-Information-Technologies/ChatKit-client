#include "connect-command.h"

using namespace chat_client_model_message_functionality;
using namespace chat_client_model_message_functionality_client_stream_in;
using json = nlohmann::json;

std::string ConnectCommand::ToString() { return this->ToJson().dump(); }

json ConnectCommand::ToJson() {
  json json_object = {{"type", "Connect"}};

  return json_object;
}