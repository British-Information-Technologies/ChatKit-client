#ifndef MODEL_NETWORKING_MESSAGES_STREAM_IN_SERVER_ERROR_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_IN_SERVER_ERROR_H_

#include "./server-stream-in.h"

#include <string>

namespace server_stream_in {
    const std::string kError = "Error";

    class Error: public model::ServerStreamIn {
        private:
            std::string msg;

        public:
            Error(std::string msg);

            std::string Serialize();
            
            model::StreamType GetStreamType();
    };
}

#endif