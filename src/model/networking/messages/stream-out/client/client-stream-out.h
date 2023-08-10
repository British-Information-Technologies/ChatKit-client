#ifndef MODEL_NETWORKING_MESSAGES_STREAM_OUT_CLIENT_STREAM_OUT_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_OUT_CLIENT_STREAM_OUT_H_

#include <string>

#include "../stream-out.h"

namespace model {
    class ClientStreamOut: public StreamOut {
        public:
            virtual std::string Serialize() = 0;
    };
}

#endif