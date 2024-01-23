#ifndef MODEL_NETWORKING_MESSAGES_STREAM_IN_NETWORK_GOT_INFO_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_IN_NETWORK_GOT_INFO_H_

#include <string>

#include "./network-stream-in.h"

namespace network_stream_in {
class GotInfo : public model::NetworkStreamIn {
private:
    const std::string server_name;
    const std::string server_owner;

public:
    GotInfo(const std::string& server_name, const std::string& server_owner);

    std::string GetServerAlias();

    std::string GetServerOwner();

    std::string Serialize();

    model::StreamType GetStreamType();
};
} // namespace network_stream_in

#endif