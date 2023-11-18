#ifndef MODEL_NETWORKING_CONNECTION_CHANNEL_WRITER_H_
#define MODEL_NETWORKING_CONNECTION_CHANNEL_WRITER_H_

#include <memory>
#include <msd/channel.hpp>
#include <event2/bufferevent.h>

#include "model/networking/utility/data.h"

#include "model/networking/messages/message.h"

namespace model {
    class ChannelWriter {
        private:
            msd::channel<Data> &output;
            
            const std::string &uuid;

        public:
            ChannelWriter(
                msd::channel<Data> &output,
                const std::string &uuid
            );

            virtual ~ChannelWriter() {}

            void SendData(
                const int fd,
                std::shared_ptr<Message> message
            );
    };
}

#endif