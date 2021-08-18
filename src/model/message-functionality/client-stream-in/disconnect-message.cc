#include "disconnect-message.h"

using namespace chat_client_model_message_functionality;
using namespace chat_client_model_message_functionality_client_stream_in;
using json = nlohmann::json;

std::string DisconnectMessage::ToString() { return this->ToJson().dump(); }

json DisconnectMessage::ToJson() {
  json json_object = {{"type", "Disconnect"}};

  return json_object;
}