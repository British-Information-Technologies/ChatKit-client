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

#define CONNECT "Connect"
#define DISCONNECTED "Disconnected"
#define ERROR "Error"
#define GLOBALMESSAGE "GlobalMessage"
#define UPDATE "Update"
#define USERMESSAGE "UserMessage"

std::unique_ptr<Message> ClientStreamInFactory::GetMessage(
    const std::string &plaintext) {
  try {
    json plaintext_object = json::parse(plaintext);
    std::string type = plaintext_object["type"];

    if (type.compare(CONNECT) == 0) {
      return std::make_unique<ConnectCommand>();
    } else if (type.compare(DISCONNECTED) == 0) {
      return std::make_unique<DisconnectedCommand>();
    } else if (type.compare(ERROR) == 0) {
      return std::make_unique<ErrorCommand>();
    } else if (type.compare(GLOBALMESSAGE) == 0) {
      std::string content = plaintext_object["content"];
      return std::make_unique<GlobalMessageCommand>(content);
    } else if (type.compare(UPDATE) == 0) {
      return std::make_unique<UpdateCommand>();
    } else if (type.compare(USERMESSAGE) == 0) {
      std::string from = plaintext_object["from"];
      std::string content = plaintext_object["content"];
      return std::make_unique<UserMessageCommand>(from, content);
    }

    return std::make_unique<InvalidCommand>();
  } catch (const json::exception &e) {
    return std::make_unique<InvalidCommand>();
  }
}