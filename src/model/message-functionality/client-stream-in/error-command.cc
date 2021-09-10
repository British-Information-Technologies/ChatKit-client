#include "error-command.h"

using namespace model_message_functionality;
using namespace model_message_functionality_client_stream_in;
using json = nlohmann::json;

std::string ErrorCommand::ToString() { return this->ToJson().dump(); }

json ErrorCommand::ToJson() {
  json json_object = {{"type", "Error"}};

  return json_object;
}