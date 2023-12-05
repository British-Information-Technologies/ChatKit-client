#ifndef MODEL_NETWORKING_MESSAGES_STREAM_IN_SERVER_STREAM_IN_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_IN_SERVER_STREAM_IN_H_

#include <string>

#include "../stream-in.h"

namespace model {
class ServerStreamIn : public StreamIn {
public:
    virtual std::string Serialize() = 0;

    virtual StreamType GetStreamType() = 0;
};
} // namespace model

#endif