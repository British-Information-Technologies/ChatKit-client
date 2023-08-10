#ifndef MODEL_NETWORKING_MESSAGES_STREAM_IN_CLIENT_STREAM_IN_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_IN_CLIENT_STREAM_IN_H_

#include <string>

#include "../stream-in.h"

namespace model {
    class ClientStreamIn: public StreamIn {
        public:
            virtual std::string Serialize() = 0;
    };
}

#endif