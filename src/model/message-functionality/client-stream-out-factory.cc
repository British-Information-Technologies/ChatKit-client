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

std::unique_ptr<Message> ClientStreamOutFactory::GetMessage(
    const std::string &type) {
  if (type.compare("Disconnect") == 0) {
    return std::make_unique<DisconnectCommand>();
  } else if (type.compare("Update") == 0) {
    return std::make_unique<UpdateCommand>();
  }

  return std::make_unique<InvalidCommand>();
}

std::unique_ptr<Message> ClientStreamOutFactory::GetMessage(
    const std::string &type, const std::string &content) {
  if (type.compare("SendGlobalMessage") == 0) {
    return std::make_unique<SendGlobalMessageCommand>(content);
  }

  return std::make_unique<InvalidCommand>();
}

std::unique_ptr<Message> ClientStreamOutFactory::GetMessage(
    const std::string &type, const std::string &to,
    const std::string &content) {
  if (type.compare("SendMessage") == 0) {
    return std::make_unique<SendMessageCommand>(to, content);
  }

  return std::make_unique<InvalidCommand>();
}