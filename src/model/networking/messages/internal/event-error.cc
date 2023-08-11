#include "event-error.h"

#include <string>
#include <fmt/core.h>

using namespace internal;

EventError::EventError(std::string msg) {
    this->msg = msg;
}

std::string EventError::Serialize() {
    return fmt::format("{{ \"type\": {}, \"msg\": {} }}", type, msg);
}

std::string EventError::GetMsg() {
    return this->msg;
}

model::StreamType EventError::GetStreamType() {
    return model::StreamType::Internal;
}