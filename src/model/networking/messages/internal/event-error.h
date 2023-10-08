#ifndef MODEL_NETWORKING_MESSAGES_INTERNAL_EVENT_ERROR_H_
#define MODEL_NETWORKING_MESSAGES_INTERNAL_EVENT_ERROR_H_

#include "./internal.h"

#include <string>

namespace internal {
    class EventError: public model::Internal {
        private:
            const std::string msg;

        public:
            EventError(const std::string &msg);

            std::string Serialize();

            std::string GetMsg();
            
            model::StreamType GetStreamType();
    };
}

#endif