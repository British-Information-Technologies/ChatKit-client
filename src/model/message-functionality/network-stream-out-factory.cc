#include "network-stream-out-factory.h"

#include "general/invalid-command.h"
#include "network-stream-out/connect-command.h"
#include "network-stream-out/info-command.h"

using namespace chat_client_model_message_functionality;
using namespace chat_client_model_message_functionality_general;
using namespace chat_client_model_message_functionality_network_stream_out;
using json = nlohmann::json;

#define INFO "Info"
#define CONNECT "Connect"

std::unique_ptr<Message> NetworkStreamOutFactory::GetMessage(
    const std::string &type) {
  if (type.compare(INFO) == 0) {
    return std::make_unique<InfoCommand>();
  }

  return std::make_unique<InvalidCommand>();
}

std::unique_ptr<Message> NetworkStreamOutFactory::GetMessage(
    const std::string &type, const std::string &uuid,
    const std::string &username, const std::string &address) {
  if (type.compare(CONNECT) == 0) {
    return std::make_unique<ConnectCommand>(uuid, username, address);
  }

  return std::make_unique<InvalidCommand>();
}