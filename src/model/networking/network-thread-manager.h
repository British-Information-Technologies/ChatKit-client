#ifndef MODEL_NETWORKING_NETWORK_THREAD_MANAGER_H_
#define MODEL_NETWORKING_NETWORK_THREAD_MANAGER_H_

#include <string>
#include <unordered_map>
#include <memory>
#include <thread>
#include <event2/event.h>

#include "model/networking/connection/connection.h"
#include "model/networking/connection/channel/channel-reader.h"

namespace model {
    class NetworkThreadManager {
        private:
            std::unique_ptr<ChannelReader> buffer_reader;
            
            std::unique_ptr<std::jthread> connection_base_thread;
            
            std::unique_ptr<std::jthread> channel_thread;

        private:
            void LaunchConnectionBaseHandler(
                std::shared_ptr<event_base> connection_base
            );
  
            void LaunchInputChannelHandler(
                std::unordered_map<std::string, std::shared_ptr<Connection>> &connections
            );

        public:
            NetworkThreadManager(
                std::unique_ptr<ChannelReader> buffer_reader
            );

            ~NetworkThreadManager();
            
            void LaunchConnectionBase(
                std::shared_ptr<event_base> connection_base
            );

            void LaunchInputChannel(
                std::unordered_map<std::string, std::shared_ptr<Connection>> &connections
            );
    };
}

#endif