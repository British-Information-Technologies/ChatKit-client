#include "client-stream-in-factory.h"

#include "client-stream-in/connect-command.h"
#include "client-stream-in/disconnected-command.h"
#include "client-stream-in/error-command.h"
#include "client-stream-in/global-message-command.h"

using namespace chat_client_model_message_functionality;
using namespace chat_client_model_message_functionality_client_stream_in;
using json = nlohmann::json;

std::unique_ptr<Message> ClientStreamInFactory::GetMessage(
    const std::string &plaintext) {
  json plaintext_object = json::parse(plaintext);
  std::string type = plaintext_object["type"];

  if (type.compare("Connect") == 0) {
    return std::make_unique<ConnectCommand>();
  } else if (type.compare("Disconnected") == 0) {
    return std::make_unique<DisconnectedCommand>();
  } else if (type.compare("Error") == 0) {
    return std::make_unique<ErrorCommand>();
  }

  std::string content = plaintext_object["content"];
  return std::make_unique<GlobalMessageCommand>(content);
}