#ifndef MODEL_NETWORKING_MESSAGES_STREAM_IN_SERVER_PUBLIC_KEY_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_IN_SERVER_PUBLIC_KEY_H_

#include "./server-stream-in.h"

#include <string>

namespace server_stream_in {
class PublicKey : public model::ServerStreamIn {
private:
    const std::string from;
    const std::string key;

public:
    PublicKey(const std::string& from, const std::string& key);

    std::string Serialize();

    std::string GetFrom();

    unsigned char* GetKey();

    model::StreamType GetStreamType();
};
} // namespace server_stream_in

#endif