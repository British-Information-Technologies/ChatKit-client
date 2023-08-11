#include <string>
#include <fmt/core.h>

#include "send-message.h"

using namespace client_stream_out;

SendMessage::SendMessage(
    std::string time,
    std::string date,
    std::string content
) {
    this->type = kSendMessage;
    this->time = time;
    this->date = date;
    this->content = content;
}

std::string SendMessage::Serialize() {
    return fmt::format("{{ \"type\": {}, \"time\": {}, \"date\": {}, \"content\": {} }}", type, time, date, content);
}

model::StreamType SendMessage::GetStreamType() {
    return model::StreamType::ClientStreamOut;
}