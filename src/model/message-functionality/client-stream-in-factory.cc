#include "client-stream-in-factory.h"

#include "client-stream-in/connect-command.h"
#include "client-stream-in/disconnected-command.h"
#include "client-stream-in/error-command.h"
#include "client-stream-in/global-message-command.h"
#include "client-stream-in/update-command.h"
#include "client-stream-in/user-message-command.h"
#include "general/invalid-command.h"

using namespace chat_client_model_message_functionality;
using namespace chat_client_model_message_functionality_client_stream_in;
using namespace chat_client_model_message_functionality_general;
using json = nlohmann::json;

std::unique_ptr<Message> ClientStreamInFactory::GetMessage(
    const std::string &plaintext) {
  try {
    json plaintext_object = json::parse(plaintext);
    std::string type = plaintext_object["type"];

    if (type.compare("Connect") == 0) {
      return std::make_unique<ConnectCommand>();
    } else if (type.compare("Disconnected") == 0) {
      return std::make_unique<DisconnectedCommand>();
    } else if (type.compare("Error") == 0) {
      return std::make_unique<ErrorCommand>();
    } else if (type.compare("GlobalMessage") == 0) {
      std::string content = plaintext_object["content"];
      return std::make_unique<GlobalMessageCommand>(content);
    } else if (type.compare("Update") == 0) {
      return std::make_unique<UpdateCommand>();
    } else if (type.compare("UserMessage") == 0) {
      std::string from = plaintext_object["from"];
      std::string content = plaintext_object["content"];
      return std::make_unique<UserMessageCommand>(from, content);
    }

    return std::make_unique<InvalidCommand>();
  } catch (const json::exception &e) {
    return std::make_unique<InvalidCommand>();
  }
}