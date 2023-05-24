#ifndef MODEL_NETWORKING_MESSAGES_STREAM_OUT_SERVER_STREAM_OUT_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_OUT_SERVER_STREAM_OUT_H_

#include <string>

#include "../stream-out.h"

class ServerStreamOut: public StreamOut {
    public:
        virtual std::string Serialize() = 0;
};

#endif