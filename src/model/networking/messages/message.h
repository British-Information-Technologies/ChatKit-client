#ifndef MODEL_NETWORKING_MESSAGES_H_
#define MODEL_NETWORKING_MESSAGES_H_

#include <string>
#include <memory>

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
            virtual std::string Serialize() = 0;

            virtual StreamType GetStreamType() = 0;

            Type GetType();
    };

    std::unique_ptr<Message> CreateClientStreamOutSendMessage(
        const std::string &time,
        const std::string &date,
        const std::string &data
    );
    
    std::unique_ptr<Message> CreateServerStreamOutPublicKey(
        const std::string &to,
        const std::string &pk
    );
    
    int DeserializeStreamIn(Message* msg, std::string &data);
    int DeserializeClientStreamIn(Message* msg, std::string &data);
    int DeserializeServerStreamIn(Message* msg, std::string &data);
    int DeserializeNetworkStreamIn(Message* msg, std::string &data);

    int DeserializeStreamOut(Message* msg, std::string &data);
    int DeserializeClientStreamOut(Message* msg, std::string &data);
    int DeserializeServerStreamOut(Message* msg, std::string &data);
    int DeserializeNetworkStreamOut(Message* msg, std::string &data);


    int DeserializeInternal(Message* msg, std::string &data);
}

#endif