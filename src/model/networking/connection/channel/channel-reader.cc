#include "channel-reader.h"

#include <memory>
#include <msd/channel.hpp>

#include "model/networking/utility/data.h"
#include "model/networking/messages/message.h"

using namespace model;

ChannelReader::ChannelReader(
    msd::channel<Data> &buffer
): buffer(buffer)
{}

Data ChannelReader::ReadData()
{
    Data data;
    
    data << buffer;

    return (
        data.message->GetStreamType() == StreamType::StreamIn
    ) ? data : Data {};
}
