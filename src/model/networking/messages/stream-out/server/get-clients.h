#ifndef MODEL_NETWORKING_MESSAGES_STREAM_OUT_SERVER_GET_CLIENTS_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_OUT_SERVER_GET_CLIENTS_H_

#include <string>

#include "./server-stream-out.h"

namespace server_stream_out {
class GetClients : public model::ServerStreamOut {
public:
    GetClients();

    std::string Serialize();

    model::StreamType GetStreamType();
};
} // namespace server_stream_out

#endif