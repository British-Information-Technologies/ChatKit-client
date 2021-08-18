#include "send-message.h"

using namespace chat_client_model_message_functionality;
using namespace chat_client_model_message_functionality_client_stream_in;
using json = nlohmann::json;

std::string SendMessage::ToString() { return this->ToJson().dump(); }

json SendMessage::ToJson() {
  json json_object = {{"type", "SendMessage"}};

  return json_object;
}