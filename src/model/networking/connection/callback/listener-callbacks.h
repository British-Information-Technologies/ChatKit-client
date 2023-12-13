#ifndef MODEL_NETWORKING_CONNECTION_CALLBACK_LISTENER_H_
#define MODEL_NETWORKING_CONNECTION_CALLBACK_LISTENER_H_

#include <event2/listener.h>

namespace model_networking_connection_callback {
void AcceptConnectionCbHandler(
    struct evconnlistener* listener,
    evutil_socket_t sockfd,
    struct sockaddr* address,
    int socklen,
    void* ptr);

void AcceptErrorCbHandler(
    struct evconnlistener* listener,
    void* ptr);
} // namespace model_networking_connection_callback

#endif