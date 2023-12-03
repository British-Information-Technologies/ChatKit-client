#ifndef MODEL_NETWORKING_MESSAGES_STREAM_IN_NETWORK_ERROR_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_IN_NETWORK_ERROR_H_

#include <string>

#include "./network-stream-in.h"

namespace network_stream_in {
class Error : public model::NetworkStreamIn {
public:
    Error();

    std::string Serialize();

    model::StreamType GetStreamType();
};
} // namespace network_stream_in

#endif