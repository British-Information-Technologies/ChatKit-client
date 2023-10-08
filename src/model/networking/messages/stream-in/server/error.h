#ifndef MODEL_NETWORKING_MESSAGES_STREAM_IN_SERVER_ERROR_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_IN_SERVER_ERROR_H_

#include "./server-stream-in.h"

#include <string>

namespace server_stream_in {
    class Error: public model::ServerStreamIn {
        private:
            const std::string msg;

        public:
            Error(const std::string &msg);

            std::string Serialize();
            
            model::StreamType GetStreamType();
    };
}

#endif