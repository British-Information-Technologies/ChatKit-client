#ifndef MODEL_NETWORKING_MESSAGES_STREAM_OUT_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_OUT_H_

#include <string>

#include "../message.h"

namespace model {
class StreamOut : public Message {
public:
    virtual std::string Serialize() = 0;

    virtual StreamType GetStreamType() = 0;
};
}// namespace model

#endif