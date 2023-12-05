#include "channel-reader.h"

#include <memory>
#include <msd/channel.hpp>
#include <optional>

#include "model/networking/messages/message.h"
#include "model/networking/utility/data.h"

using namespace model;

ChannelReader::ChannelReader(
    std::shared_ptr<msd::channel<Data>> buffer) : buffer(buffer) {}

std::optional<Data> ChannelReader::ReadData() {
    Data data;

    data << *buffer;

    return data.message->GetStreamType() == StreamType::StreamIn ? std::optional<Data>{data} : std::nullopt;
}
