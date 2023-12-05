#include "channel-writer.h"

#include <event2/bufferevent.h>
#include <memory>
#include <msd/channel.hpp>

#include "model/networking/messages/message.h"
#include "model/networking/utility/data.h"

using namespace model;

ChannelWriter::ChannelWriter(
    std::shared_ptr<msd::channel<Data>> buffer) : buffer(buffer) {}

void ChannelWriter::SendData(
    const std::string& uuid,
    const int fd,
    std::shared_ptr<Message> message) {
    std::move(Data{uuid, fd, message}) >> *buffer;
}
