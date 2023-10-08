#ifndef MODEL_NETWORKING_UTILITY_DATA_H_
#define MODEL_NETWORKING_UTILITY_DATA_H_

#include <memory>

#include "model/networking/messages/message.h"

namespace model{
    struct Data {
        std::string uuid;
        int sockfd;
        std::shared_ptr<Message> message;
    };
} // namespace model

#endif