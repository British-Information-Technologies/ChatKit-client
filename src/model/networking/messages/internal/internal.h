#ifndef MODEL_NETWORKING_MESSAGES_INTERNAL_H_
#define MODEL_NETWORKING_MESSAGES_INTERNAL_H_

#include <string>

#include "../message.h"

namespace model {
class Internal : public Message {
public:
    virtual ~Internal() {}
    virtual std::string Serialize() = 0;

    virtual StreamType GetStreamType() = 0;
};
} // namespace model

#endif
