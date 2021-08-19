#include "connect-message.h"

using namespace chat_client_model_message_functionality;
using namespace chat_client_model_message_functionality_client_stream_out;
using json = nlohmann::json;

std::string ConnectMessage::ToString() { return this->ToJson().dump(); }

json ConnectMessage::ToJson() {
  json json_object = {{"type", "Connect"}};

  return json_object;
}