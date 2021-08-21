#include "client-stream-out-factory.h"

#include "client-stream-out/disconnect-command.h"

using namespace chat_client_model_message_functionality;
using namespace chat_client_model_message_functionality_client_stream_out;
using json = nlohmann::json;

std::unique_ptr<Message> ClientStreamOutFactory::GetMessage() {
  return std::make_unique<DisconnectCommand>();
}