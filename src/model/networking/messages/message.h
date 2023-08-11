#ifndef MODEL_NETWORKING_MESSAGES_H_
#define MODEL_NETWORKING_MESSAGES_H_

#include <string>

namespace model {
    enum StreamType {
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

    class Message {
        protected:
            std::string type;

        public:
            virtual std::string Serialize() = 0;

            virtual StreamType GetStreamType() = 0;

            std::string GetType();
    };
    
    int DeserializeStreamIn(Message* msg, std::string data);
    int DeserializeClientStreamIn(Message* msg, std::string data);
    int DeserializeServerStreamIn(Message* msg, std::string data);
    int DeserializeNetworkStreamIn(Message* msg, std::string data);

    int DeserializeStreamOut(Message* msg, std::string data);
    int DeserializeClientStreamOut(Message* msg, std::string data);
    int DeserializeServerStreamOut(Message* msg, std::string data);
    int DeserializeNetworkStreamOut(Message* msg, std::string data);


    int DeserializeInternal(Message* msg, std::string data);
}

#endif