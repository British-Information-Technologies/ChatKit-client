#ifndef MODEL_NETWORKING_CONNECTION_CALLBACK_LISTENER_H_
#define MODEL_NETWORKING_CONNECTION_CALLBACK_LISTENER_H_

#include <event2/listener.h>

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