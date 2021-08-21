#include "client-stream-out-factory.h"

#include "client-stream-out/disconnect-command.h"
#include "client-stream-out/send-global-message-command.h"
#include "client-stream-out/send-message-command.h"

using namespace chat_client_model_message_functionality;
using namespace chat_client_model_message_functionality_client_stream_out;
using json = nlohmann::json;

std::unique_ptr<Message> ClientStreamOutFactory::GetMessage(
    const std::string &type) {
  return std::make_unique<DisconnectCommand>();
}

std::unique_ptr<Message> ClientStreamOutFactory::GetMessage(
    const std::string &type, const std::string &content) {
  return std::make_unique<SendGlobalMessageCommand>(content);
}

std::unique_ptr<Message> ClientStreamOutFactory::GetMessage(
    const std::string &type, const std::string &to,
    const std::string &content) {
  return std::make_unique<SendMessageCommand>(to, content);
}