#include "network-stream-out-factory.h"

#include "network-stream-out/connect-command.h"

using namespace chat_client_model_message_functionality;
using namespace chat_client_model_message_functionality_network_stream_out;
using json = nlohmann::json;

std::unique_ptr<Message> NetworkStreamOutFactory::GetMessage() {
  return std::make_unique<ConnectCommand>("1234", "mitch", "no address haha!");
}