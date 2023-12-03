#include "channel-writer.h"

#include <memory>
#include <msd/channel.hpp>
#include <event2/bufferevent.h>

#include "model/networking/utility/data.h"
#include "model/networking/messages/message.h"

using namespace model;

ChannelWriter::ChannelWriter(
    std::shared_ptr<msd::channel<Data>> buffer
): buffer(buffer)
{}

void ChannelWriter::SendData(
    const std::string &uuid,
    const int fd,
    std::shared_ptr<Message> message
)
{
    std::move(Data{ uuid, fd, message }) >> *buffer;
}
