#include "key-command.h"

using namespace model_message_functionality;
using namespace model_message_functionality_network_stream_in;
using json = nlohmann::json;

KeyCommand::KeyCommand(const std::string &key) { this->key = key; }

std::string KeyCommand::ToString() { return this->ToJson().dump(); }

json KeyCommand::ToJson() {
  json json_object = {{"type", "Key"}, {"key", key}};

  return json_object;
}