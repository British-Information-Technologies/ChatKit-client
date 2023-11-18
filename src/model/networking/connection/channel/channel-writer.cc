#include "channel-writer.h"

#include <memory>
#include <msd/channel.hpp>
#include <event2/bufferevent.h>

#include "model/networking/utility/data.h"
#include "model/networking/messages/message.h"

using namespace model;

ChannelWriter::ChannelWriter(
    msd::channel<Data> &output,
    const std::string &uuid
): output(output), uuid(uuid)
{}

void ChannelWriter::SendData(
    const int fd,
    std::shared_ptr<Message> message
)
{
    std::move(Data{ uuid, fd, message }) >> output;
}
