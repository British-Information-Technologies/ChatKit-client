#ifndef MODEL_NETWORKING_MESSAGES_STREAM_IN_SERVER_CLIENT_REMOVED_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_IN_SERVER_CLIENT_REMOVED_H_

#include <string>

#include "./server-stream-in.h"

namespace server_stream_in {
class ClientRemoved : public model::ServerStreamIn {
private:
    const std::string id;

public:
    ClientRemoved(const std::string& id);

    std::string Serialize();

    model::StreamType GetStreamType();
};
}// namespace server_stream_in

#endif