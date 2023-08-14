#ifndef MODEL_NETWORK_MODEL_H_
#define MODEL_NETWORK_MODEL_H_

#include <memory>
#include <string>

#include "networking/network-manager.h"

namespace model {
    class NetworkModel {
        private:
            std::shared_ptr<NetworkManager> network_manager;

        public:
            NetworkModel(
                std::shared_ptr<NetworkManager> network_manager
            );
            
            int Run();

            int CreateClientConnection(
                const std::string &uuid,
                const std::string &ip_address,
                const std::string &port
            );

            int SendMessage(const std::string &uuid, std::string &data);
    };
}  // namespace model

#endif