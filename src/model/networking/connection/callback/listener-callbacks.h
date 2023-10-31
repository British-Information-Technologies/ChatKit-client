#ifndef MODEL_NETWORKING_CONNECTION_CALLBACK_LISTENER_H_
#define MODEL_NETWORKING_CONNECTION_CALLBACK_LISTENER_H_

#include <event2/event.h>
#include <event2/bufferevent.h>

#include "model/networking/connection/connection.h"
#include "model/networking/connection/callback/io-callbacks.h"

namespace model {
    class ListenerCallbacks {
        public:
            static void AcceptConnectionCbHandler(
                struct evconnlistener *listener,
                evutil_socket_t sockfd,
                struct sockaddr *address,
                int socklen,
                void *ptr
            );

            static void AcceptErrorCbHandler(
                struct evconnlistener *listener,
                void *ptr
            );    
    };
}

#endif