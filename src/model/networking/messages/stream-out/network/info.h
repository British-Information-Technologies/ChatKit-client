#ifndef MODEL_NETWORKING_MESSAGES_STREAM_OUT_NETWORK_INFO_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_OUT_NETWORK_INFO_H_

#include <string>

#include "./network-stream-out.h"

namespace network_stream_out {
class Info : public model::NetworkStreamOut {
public:
    Info();

    std::string Serialize();

    model::StreamType GetStreamType();
};
}// namespace network_stream_out

#endif