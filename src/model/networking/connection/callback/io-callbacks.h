#ifndef MODEL_NETWORKING_CONNECTION_CALLBACK_IO_H_
#define MODEL_NETWORKING_CONNECTION_CALLBACK_IO_H_

#include <event2/event.h>
#include <event2/bufferevent.h>

#include "model/networking/connection/connection.h"

namespace model {
    class IOCallbacks {
        public:
            static void ReadMessageClientCbHandler(
                struct bufferevent *bev,
                void *ptr
            );

            static void ReadMessageServerCbHandler(
                struct bufferevent *bev,
                void *ptr
            );
      
            static void WriteMessageCbHandler(
                struct bufferevent *bev,
                void *ptr
            );

            static void EventCbHandler(
                struct bufferevent *bev,
                short events,
                void *ptr
            );
        
            static void SetClientConnectionCallbacks(
                struct bufferevent *bev,
                Connection *connection
            );

            static void SetServerConnectionCallbacks(
                struct bufferevent *bev,
                Connection *connection
            );
    };
}

#endif