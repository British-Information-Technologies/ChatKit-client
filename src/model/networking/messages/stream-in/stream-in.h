#ifndef MODEL_NETWORKING_MESSAGES_STREAM_IN_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_IN_H_

#include <string>

#include "../message.h"

class StreamIn: public Message {
    public:
        virtual std::string Serialize() = 0;
};

#endif