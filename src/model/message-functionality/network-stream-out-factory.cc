#include "network-stream-out-factory.h"

#include "general/invalid-command.h"
#include "network-stream-out/connect-command.h"
#include "network-stream-out/encrypt-command.h"
#include "network-stream-out/info-command.h"

using namespace model_message_functionality;
using namespace model_message_functionality_general;
using namespace model_message_functionality_network_stream_out;
using json = nlohmann::json;

#define INFO "Info"
#define CONNECT "Connect"
#define ENCRYPT "Encrypt"

std::unique_ptr<Message> NetworkStreamOutFactory::GetMessage(
    const std::string &plaintext) {
  try {
    json plaintext_object = json::parse(plaintext);
    std::string type = plaintext_object["type"];

    if (type.compare(INFO) == 0) {
      return std::make_unique<InfoCommand>();
    } else if (type.compare(CONNECT) == 0) {
      std::string uuid = plaintext_object["uuid"];
      std::string username = plaintext_object["username"];
      std::string address = plaintext_object["address"];
      return std::make_unique<ConnectCommand>(uuid, username, address);
    } else if (type.compare(ENCRYPT) == 0) {
      std::string key = plaintext_object["key"];
      return std::make_unique<EncryptCommand>(key);
    }

    return std::make_unique<InvalidCommand>();
  } catch (const json::exception &e) {
    return std::make_unique<InvalidCommand>();
  }
}