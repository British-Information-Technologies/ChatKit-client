#ifndef MODEL_NETWORKING_MESSAGES_STREAM_IN_SERVER_CONNECTED_CLIENTS_H_
#define MODEL_NETWORKING_MESSAGES_STREAM_IN_SERVER_CONNECTED_CLIENTS_H_

#include <nlohmann/json.hpp>
#include <string>

#include "./server-stream-in.h"

using json = nlohmann::json;

namespace server_stream_in {
    const std::string kConnectedClients = "ConnectedClients";
    
    class ConnectedClients: public model::ServerStreamIn {
        private:
            json clients;

        public:
            ConnectedClients(json clients);

            std::string Serialize();
            
            model::StreamType GetStreamType();
    };
}

#endif