#ifndef MODEL_NETWORKING_MESSAGES_STREAM_IN_NETWORK_CONNECTING_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_IN_NETWORK_CONNECTING_H_

#include <string>

#include "./network-stream-in.h"

namespace network_stream_in {
class Connecting : public model::NetworkStreamIn {
public:
    Connecting();

    std::string Serialize();

    model::StreamType GetStreamType();
};
}// namespace network_stream_in

#endif