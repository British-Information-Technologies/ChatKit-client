#ifndef MODEL_NETWORKING_CONNECTION_CHANNEL_WRITER_H_
#define MODEL_NETWORKING_CONNECTION_CHANNEL_WRITER_H_

#include <event2/bufferevent.h>
#include <memory>
#include <msd/channel.hpp>

#include "model/networking/utility/data.h"

#include "model/networking/messages/message.h"

namespace model {
class ChannelWriter {
private:
    std::shared_ptr<msd::channel<Data>> buffer;

public:
    ChannelWriter(
        std::shared_ptr<msd::channel<Data>> buffer);

    virtual ~ChannelWriter() {}

    void SendData(
        const std::string& uuid,
        const int fd,
        std::shared_ptr<Message> message);
};
} // namespace model

#endif