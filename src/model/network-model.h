#ifndef MODEL_NETWORK_MODEL_H_
#define MODEL_NETWORK_MODEL_H_

#include <memory>
#include <string>

#include "networking/network-manager.h"
#include "networking/connection.h"

namespace model {
    class NetworkModel {
        private:
            std::shared_ptr<NetworkManager> network_manager;

        public:
            NetworkModel();
            
            int Run();

            int SendMessage(const int &, std::string &);
    };
}  // namespace model

#endif