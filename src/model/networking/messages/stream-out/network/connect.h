#ifndef MODEL_NETWORKING_MESSAGES_STREAM_OUT_NETWORK_CONNECT_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_OUT_NETWORK_CONNECT_H_

#include <string>

#include "./network-stream-out.h"

namespace network_stream_out {
class Connect : public model::NetworkStreamOut {
private:
    const std::string uuid;
    const std::string username;
    const std::string address;

public:
    Connect(const std::string& uuid, const std::string& username, const std::string& address);

    std::string Serialize();

    model::StreamType GetStreamType();
};
} // namespace network_stream_out

#endif