#ifndef MODEL_NETWORKING_MESSAGES_INTERNAL_EVENT_ERROR_H_
#define MODEL_NETWORKING_MESSAGES_INTERNAL_EVENT_ERROR_H_

#include "./internal.h"

#include <string>

namespace internal {
    const std::string kEventError = "EventError";

    class EventError: public model::Internal {
        private:
            std::string msg;

        public:
            EventError(std::string msg);

            std::string Serialize();

            std::string GetMsg();
    };
}

#endif