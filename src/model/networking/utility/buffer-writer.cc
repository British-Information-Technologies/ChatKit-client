#include <event2/bufferevent.h>
#include <memory>
#include <string>

#include "buffer-writer.h"

int model::WriteBufferLine(std::shared_ptr<bufferevent> bev, std::string message) {
    message.push_back('\n');

    size_t len = message.length();
    if (bufferevent_write(bev.get(), message.c_str(), len) != 0) {
        return -1;
    }

    return len;
}