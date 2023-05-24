#ifndef MODEL_NETWORKING_MESSAGES_H_
#define MODEL_NETWORKING_MESSAGES_H_

#include <string>

class Message {
    protected:
        std::string type;

    public:
        virtual std::string Serialize() = 0;

        std::string GetType();
};

int Deserialize(Message* msg, std::string data, int is_stream_in);
    
int Deserialize(Message* msg, std::string data);

#endif