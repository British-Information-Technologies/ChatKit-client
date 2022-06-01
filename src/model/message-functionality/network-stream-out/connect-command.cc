#include "connect-command.h"

using namespace model_message_functionality;
using namespace model_message_functionality_network_stream_out;
using json = nlohmann::json;

ConnectCommand::ConnectCommand(const std::string &uuid,
                               const std::string &username,
                               const std::string &address) {
  this->uuid = uuid;
  this->username = username;
  this->address = address;
}

std::string ConnectCommand::ToString() { return this->ToJson().dump(); }

json ConnectCommand::ToJson() {
  json json_object = {{"type", "Connect"},
                      {"uuid", this->uuid},
                      {"username", this->username},
                      {"address", this->address}};

  return json_object;
}