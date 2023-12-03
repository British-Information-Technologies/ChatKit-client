#ifndef MODEL_NETWORKING_CONNECTION_CHANNEL_READER_H_
#define MODEL_NETWORKING_CONNECTION_CHANNEL_READER_H_

#include <memory>
#include <msd/channel.hpp>
#include <optional>

#include "model/networking/utility/data.h"
#include "model/networking/messages/message.h"

namespace model {
    class ChannelReader {
        private:
            std::shared_ptr<msd::channel<Data>> buffer;
            
        public:
            ChannelReader(
                std::shared_ptr<msd::channel<Data>> buffer
            );

            virtual ~ChannelReader() {}

            std::optional<Data> ReadData();
    };
}

#endif