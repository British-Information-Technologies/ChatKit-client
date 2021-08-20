#include "got-info-command.h"

using namespace chat_client_model_message_functionality;
using namespace chat_client_model_message_functionality_network_stream_in;
using json = nlohmann::json;

GotInfoCommand::GotInfoCommand(const std::string &server_name,
                               const std::string &server_owner) {
  this->server_name = server_name;
  this->server_owner = server_owner;
}

std::string GotInfoCommand::ToString() { return this->ToJson().dump(); }

json GotInfoCommand::ToJson() {
  json json_object = {{"type", "GotInfo"}};

  return json_object;
}