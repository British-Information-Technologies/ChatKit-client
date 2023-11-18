#ifndef MODEL_NETWORKING_CONNECTION_INJECTOR_H_
#define MODEL_NETWORKING_CONNECTION_INJECTOR_H_

#include <memory>
#include <msd/channel.hpp>

#include "model/networking/connection/connection.h"

namespace model {
    class Injector {
        public:
            static std::shared_ptr<Connection> inject_connection(
                const ConnectionType type,
                const std::string &uuid,
                std::shared_ptr<event_base> base,
                const std::string &ip_address,
                const std::string &port,
                msd::channel<model::Data> &output
            );
    };
}

#endif