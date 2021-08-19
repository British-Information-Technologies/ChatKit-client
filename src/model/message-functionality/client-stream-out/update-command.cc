#include "update-command.h"

using namespace chat_client_model_message_functionality;
using namespace chat_client_model_message_functionality_client_stream_out;
using json = nlohmann::json;

std::string UpdateCommand::ToString() { return this->ToJson().dump(); }

json UpdateCommand::ToJson() {
  json json_object = {{"type", "Update"}};

  return json_object;
}