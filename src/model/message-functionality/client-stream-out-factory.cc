#include "client-stream-out-factory.h"

#include "client-stream-out/disconnect-command.h"
#include "client-stream-out/send-global-message-command.h"
#include "client-stream-out/send-message-command.h"
#include "client-stream-out/update-command.h"
#include "general/invalid-command.h"

using namespace chat_client_model_message_functionality;
using namespace chat_client_model_message_functionality_client_stream_out;
using namespace chat_client_model_message_functionality_general;
using json = nlohmann::json;

#define DISCONNECT "Disconnect"
#define UPDATE "Update"
#define SENDGLOBALMESSAGE "SendGlobalMessage"
#define SENDMESSAGE "SendMessage"

std::unique_ptr<Message> ClientStreamOutFactory::GetMessage(
    const std::string &plaintext) {
  try {
    json plaintext_object = json::parse(plaintext);
    std::string type = plaintext_object["type"];

    if (type.compare(DISCONNECT) == 0) {
      return std::make_unique<DisconnectCommand>();
    } else if (type.compare(UPDATE) == 0) {
      return std::make_unique<UpdateCommand>();
    } else if (type.compare(SENDGLOBALMESSAGE) == 0) {
      std::string content = plaintext_object["content"];
      return std::make_unique<SendGlobalMessageCommand>(content);
    } else if (type.compare(SENDMESSAGE) == 0) {
      std::string to = plaintext_object["to"];
      std::string content = plaintext_object["content"];
      return std::make_unique<SendMessageCommand>(to, content);
    }

    return std::make_unique<InvalidCommand>();
  } catch (const json::exception &e) {
    return std::make_unique<InvalidCommand>();
  }
}