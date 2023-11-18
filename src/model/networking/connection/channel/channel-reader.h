#ifndef MODEL_NETWORKING_CONNECTION_CHANNEL_READER_H_
#define MODEL_NETWORKING_CONNECTION_CHANNEL_READER_H_

#include <memory>
#include <msd/channel.hpp>

#include "model/networking/utility/data.h"
#include "model/networking/messages/message.h"

namespace model {
    class ChannelReader {
        private:
            msd::channel<Data> &buffer;
            
        public:
            ChannelReader(msd::channel<Data> &buffer);

            virtual ~ChannelReader() {}

            Data ReadData();
    };
}

#endif