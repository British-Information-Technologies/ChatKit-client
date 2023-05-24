#ifndef MODEL_NETWORKING_MESSAGES_STREAM_OUT_NETWORK_STREAM_OUT_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_OUT_NETWORK_STREAM_OUT_H_

#include <string>

#include "../stream-out.h"

class NetworkStreamOut: public StreamOut {
    public:
        virtual std::string Serialize() = 0;
};

#endif