#ifndef MODEL_NETWORKING_CONNECTION_CHANNEL_HANDLER_H_
#define MODEL_NETWORKING_CONNECTION_CHANNEL_HANDLER_H_

#include <memory>
#include <msd/channel.hpp>
#include <event2/bufferevent.h>

#include "model/networking/utility/data.h"

#include "model/networking/messages/message.h"

namespace model {
    class ChannelHandler {
        private:
            msd::channel<Data> &out_chann;
            
            const std::string &uuid;
            
            std::shared_ptr<bufferevent> bev;

        public:
            ChannelHandler(
                msd::channel<Data> &out_chann,
                const std::string &uuid,
                std::shared_ptr<bufferevent> bev
            );

            virtual ~ChannelHandler() {}

            void SendData(std::shared_ptr<Message> message);
    };
}

#endif