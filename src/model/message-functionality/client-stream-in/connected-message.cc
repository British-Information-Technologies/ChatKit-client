#include "connected-message.h"

using namespace chat_client_model_message_functionality;
using namespace chat_client_model_message_functionality_client_stream_in;
using json = nlohmann::json;

std::string ConnectedMessage::ToString() { return this->ToJson().dump(); }

json ConnectedMessage::ToJson() {
  json json_object = {{"type", "connect"}};

  return json_object;
}