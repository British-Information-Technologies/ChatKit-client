#include "client-stream-in-factory.h"

#include "client-stream-in/connect-command.h"

using namespace chat_client_model_message_functionality;
using namespace chat_client_model_message_functionality_client_stream_in;

std::unique_ptr<Message> ClientStreamInFactory::GetMessage(
    const std::string &plaintext) {
  ConnectCommand connect_command;
  return std::make_unique<ConnectCommand>(connect_command);
}