#include "network-stream-in-factory.h"

#include "general/invalid-command.h"
#include "network-stream-in/connecting-command.h"
#include "network-stream-in/got-info-command.h"
#include "network-stream-in/request-command.h"

using namespace chat_client_model_message_functionality;
using namespace chat_client_model_message_functionality_network_stream_in;
using namespace chat_client_model_message_functionality_general;
using json = nlohmann::json;

std::unique_ptr<Message> NetworkStreamInFactory::GetMessage(
    const std::string &plaintext) {
  try {
    json plaintext_object = json::parse(plaintext);
    std::string type = plaintext_object["type"];

    if (type.compare("Connecting") == 0) {
      return std::make_unique<ConnectingCommand>();
    } else if (type.compare("GotInfo") == 0) {
      std::string server_name = plaintext_object["server name"];
      std::string server_owner = plaintext_object["server owner"];

      return std::make_unique<GotInfoCommand>(server_name, server_owner);
    } else if (type.compare("Request") == 0) {
      return std::make_unique<RequestCommand>();
    }

    return std::make_unique<InvalidCommand>();
  } catch (json::exception &e) {
    return std::make_unique<InvalidCommand>();
  }
}