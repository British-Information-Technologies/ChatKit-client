#include "error-message.h"

using namespace chat_client_model_message_functionality;
using namespace chat_client_model_message_functionality_client_stream_out;
using json = nlohmann::json;

std::string ErrorMessage::ToString() { return this->ToJson().dump(); }

json ErrorMessage::ToJson() {
  json json_object = {{"type", "Error"}};

  return json_object;
}