#include "encrypt-command.h"

using namespace chat_client_model_message_functionality;
using namespace chat_client_model_message_functionality_network_stream_out;
using json = nlohmann::json;

EncryptCommand::EncryptCommand(const std::string &key) { this->key = key; }

std::string EncryptCommand::ToString() { return this->ToJson().dump(); }

json EncryptCommand::ToJson() {
  json json_object = {{"type", "Encrypt"}, {"key", this->key}};

  return json_object;
}