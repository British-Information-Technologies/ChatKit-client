#include "network-stream-in-factory.h"

#include "general/invalid-command.h"
#include "network-stream-in/connecting-command.h"
#include "network-stream-in/got-info-command.h"
#include "network-stream-in/key-command.h"
#include "network-stream-in/request-command.h"

using namespace model_message_functionality;
using namespace model_message_functionality_network_stream_in;
using namespace model_message_functionality_general;
using json = nlohmann::json;

#define CONNECTING "Connecting"
#define GOTINFO "GotInfo"
#define REQUEST "Request"
#define KEY "Key"

std::unique_ptr<Message> NetworkStreamInFactory::GetMessage(
    const std::string &plaintext) {
  try {
    json plaintext_object = json::parse(plaintext);
    std::string type = plaintext_object["type"];

    if (type.compare(CONNECTING) == 0) {
      return std::make_unique<ConnectingCommand>();
    } else if (type.compare(GOTINFO) == 0) {
      std::string server_name = plaintext_object["server name"];
      std::string server_owner = plaintext_object["server owner"];

      return std::make_unique<GotInfoCommand>(server_name, server_owner);
    } else if (type.compare(REQUEST) == 0) {
      return std::make_unique<RequestCommand>();
    } else if (type.compare(KEY) == 0) {
      std::string key = plaintext_object["key"];
      return std::make_unique<KeyCommand>(key);
    }

    return std::make_unique<InvalidCommand>();
  } catch (json::exception &e) {
    return std::make_unique<InvalidCommand>();
  }
}