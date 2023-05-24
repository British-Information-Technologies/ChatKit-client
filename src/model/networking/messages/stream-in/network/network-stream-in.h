#ifndef MODEL_NETWORKING_MESSAGES_STREAM_IN_NETWORK_STREAM_IN_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_IN_NETWORK_STREAM_IN_H_

#include <string>

#include "../stream-in.h"

class NetworkStreamIn: public StreamIn {
    public:
        virtual std::string Serialize() = 0;
};

#endif