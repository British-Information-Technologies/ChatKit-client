#include "channel-handler.h"

#include <memory>
#include <msd/channel.hpp>
#include <event2/bufferevent.h>

#include "model/networking/messages/message.h"

using namespace model;

ChannelHandler::ChannelHandler(
    msd::channel<Data> &out_chann,
    const std::string &uuid,
    std::shared_ptr<bufferevent> bev
): out_chann(out_chann), uuid(uuid), bev(bev)
{}

void ChannelHandler::SendData(
    std::shared_ptr<Message> message
)
{
    std::move(Data{ uuid, bufferevent_getfd(bev.get()), message }) >> out_chann;
}
