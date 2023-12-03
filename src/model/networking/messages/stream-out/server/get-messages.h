#ifndef MODEL_NETWORKING_MESSAGES_STREAM_OUT_SERVER_GET_MESSAGES_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_OUT_SERVER_GET_MESSAGES_H_

#include <string>

#include "./server-stream-out.h"

namespace server_stream_out {
class GetMessages : public model::ServerStreamOut {
public:
    GetMessages();

    std::string Serialize();

    model::StreamType GetStreamType();
};
}// namespace server_stream_out

#endif