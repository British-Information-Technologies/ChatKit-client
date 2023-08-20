#include <string>
#include <fmt/core.h>
#include <magic_enum.hpp>

#include "send-message.h"

using namespace client_stream_out;

SendMessage::SendMessage(
    const std::string &time,
    const std::string &date,
    const std::string &content
): time(time), date(date), content(content)
{
    this->type = model::Type::SendMessage;
}

std::string SendMessage::Serialize() {
    return fmt::format("{{ \"type\": {}, \"time\": {}, \"date\": {}, \"content\": {} }}", magic_enum::enum_name(type), time, date, content);
}

model::StreamType SendMessage::GetStreamType() {
    return model::StreamType::ClientStreamOut;
}