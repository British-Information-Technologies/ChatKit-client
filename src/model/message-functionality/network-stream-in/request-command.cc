#include "request-command.h"

using namespace chat_client_model_message_functionality;
using namespace chat_client_model_message_functionality_network_stream_in;
using json = nlohmann::json;

std::string RequestCommand::ToString() { return this->ToJson().dump(); }

json RequestCommand::ToJson() {
  json json_object = {{"type", "Request"}};

  return json_object;
}