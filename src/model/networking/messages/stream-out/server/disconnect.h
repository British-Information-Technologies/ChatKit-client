#ifndef MODEL_NETWORKING_MESSAGES_STREAM_OUT_SERVER_DISCONNECT_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_OUT_SERVER_DISCONNECT_H_

#include <string>

#include "./server-stream-out.h"

namespace server_stream_out {
class Disconnect : public model::ServerStreamOut {
public:
    Disconnect();

    std::string Serialize();

    model::StreamType GetStreamType();
};
} // namespace server_stream_out

#endif