#include "event-error.h"

#include <fmt/core.h>
#include <magic_enum.hpp>
#include <string>

using namespace internal;

EventError::EventError(const std::string& msg) : msg(msg) {
    this->type = model::Type::EventError;
}

std::string EventError::Serialize() {
    return fmt::format("{{ \"type\": {}, \"msg\": {} }}", magic_enum::enum_name(type), msg);
}

std::string EventError::GetMsg() {
    return this->msg;
}

model::StreamType EventError::GetStreamType() {
    return model::StreamType::Internal;
}