#include "connect-command.h"

using namespace model_message_functionality;
using namespace model_message_functionality_client_stream_in;
using json = nlohmann::json;

std::string ConnectCommand::ToString() { return this->ToJson().dump(); }

json ConnectCommand::ToJson() {
  json json_object = {{"type", "Connect"}};

  return json_object;
}