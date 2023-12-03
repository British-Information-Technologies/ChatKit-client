#ifndef MODEL_NETWORKING_MESSAGES_H_
#define MODEL_NETWORKING_MESSAGES_H_

#include <memory>
#include <string>

namespace model {
enum class StreamType {
    StreamIn,
    ClientStreamIn,
    ServerStreamIn,
    NetworkStreamIn,

    StreamOut,
    ClientStreamOut,
    ServerStreamOut,
    NetworkStreamOut,

    Internal
};

enum class Type {
    EventError,

    Error,
    PublicKey,
    SendMessage,

    Connecting,
    GotInfo,
    Request,

    ClientConnected,
    ClientRemoved,
    ConnectedClients,
    Connected,
    Disconnected,
    GlobalChatMessages,
    GlobalMessage,
    UserMessage,

    Connect,
    Info,

    Disconnect,
    GetClients,
    GetMessages,
    SendGlobalMessage
};

class Message {
protected:
    Type type;

public:
    virtual ~Message(){};
    virtual std::string Serialize() = 0;

    virtual StreamType GetStreamType() = 0;

    Type GetType();
};

std::unique_ptr<Message> CreateClientStreamOutSendMessage(
    const std::string& time,
    const std::string& date,
    const std::string& data);

std::unique_ptr<Message> CreateServerStreamOutPublicKey(
    const std::string& to,
    const std::string& pk);

Message* DeserializeStreamIn(std::string& data);
Message* DeserializeClientStreamIn(std::string& data);
Message* DeserializeServerStreamIn(std::string& data);
Message* DeserializeNetworkStreamIn(std::string& data);

Message* DeserializeStreamOut(std::string& data);
Message* DeserializeClientStreamOut(std::string& data);
Message* DeserializeServerStreamOut(std::string& data);
Message* DeserializeNetworkStreamOut(std::string& data);

Message* DeserializeInternal(std::string& data);
}// namespace model

#endif
