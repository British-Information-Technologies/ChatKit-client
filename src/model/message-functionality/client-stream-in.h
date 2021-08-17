#ifndef CPPCHATCLIENT_MODEL_MESSAGEFUNCTIONALITY_CLIENTSTREAMIN_
#define CPPCHATCLIENT_MODEL_MESSAGEFUNCTIONALITY_CLIENTSTREAMIN_

namespace chat_client_model_message_functionality {
enum class ClientStreamIn {
  Connect,
  Update,
  SendMessage,
  SendGlobalMessage,
  Disconnect
};
}

#endif