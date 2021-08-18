#include "send-global-message.h"

using namespace chat_client_model_message_functionality;
using namespace chat_client_model_message_functionality_client_stream_in;
using json = nlohmann::json;

std::string SendGlobalMessage::ToString() { return this->ToJson().dump(); }

json SendGlobalMessage::ToJson() {
  json json_object = {{"type", "SendGlobalMessage"}};

  return json_object;
}