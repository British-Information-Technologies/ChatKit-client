#include "update-message.h"

using namespace chat_client_model_message_functionality;
using namespace chat_client_model_message_functionality_client_stream_out;
using json = nlohmann::json;

std::string UpdateMessage::ToString() { return this->ToJson().dump(); }

json UpdateMessage::ToJson() {
  json json_object = {{"type", "Update"}};

  return json_object;
}