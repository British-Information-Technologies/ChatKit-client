#include "disconnected-message.h"

using namespace chat_client_model_message_functionality;
using namespace chat_client_model_message_functionality_client_stream_out;
using json = nlohmann::json;

std::string DisconnectedMessage::ToString() { return this->ToJson().dump(); }

json DisconnectedMessage::ToJson() {
  json json_object = {{"type", "Disconnected"}};

  return json_object;
}