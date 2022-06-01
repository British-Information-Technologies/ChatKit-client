#include "got-info-command.h"

using namespace model_message_functionality;
using namespace model_message_functionality_network_stream_in;
using json = nlohmann::json;

GotInfoCommand::GotInfoCommand(const std::string &server_name,
                               const std::string &server_owner) {
  this->server_name = server_name;
  this->server_owner = server_owner;
}

std::string GotInfoCommand::ToString() { return this->ToJson().dump(); }

json GotInfoCommand::ToJson() {
  json json_object = {{"type", "GotInfo"},
                      {"server name", this->server_name},
                      {"server owner", this->server_owner}};

  return json_object;
}