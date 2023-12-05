#include "listener-callbacks.h"

#include <bits/stdc++.h>
#include <event2/bufferevent.h>
#include <event2/event.h>
#include <event2/listener.h>
#include <iostream>
#include <memory>

#include "model/networking/connection/callback/io-callbacks.h"
#include "model/networking/connection/connection.h"

using namespace model;

void ListenerCallbacks::AcceptConnectionCbHandler(
    struct evconnlistener* listener,
    evutil_socket_t sockfd,
    struct sockaddr* address,
    int socklen,
    void* ptr) {
    // create new bufferevent and set its socket fd
    bufferevent* bev = bufferevent_socket_new(
        evconnlistener_get_base(listener),
        sockfd,
        BEV_OPT_CLOSE_ON_FREE);

    // cast connection
    Connection* connection = static_cast<Connection*>(ptr);

    // set tunnel callbacks
    switch (connection->tunnel->GetType()) {
    case TunnelType::Client:
        IOCallbacks::SetClientConnectionCallbacks(bev, connection);
        break;

    case TunnelType::Server:
        IOCallbacks::SetServerConnectionCallbacks(bev, connection);
    }

    // enable the bufferevent read and write
    if (bufferevent_enable(bev, EV_READ | EV_WRITE) != 0) {
        // panic! failed to enable event socket read and write
        return;
    }

    // set connection bev
    connection->tunnel->SetBev(bev);

    // free the listener, no longer needed as bev created
    connection->listener->SetState(EventListenerState::Idle);

    // finished listen
    std::cout << "[ListenerCallbacks]: connecting to " << address->sa_data << std::endl;
}

void ListenerCallbacks::AcceptErrorCbHandler(
    struct evconnlistener* listener,
    void* ptr) {
    int err = EVUTIL_SOCKET_ERROR();

    fprintf(stderr, "[ListenerCallbacks]: listener error = %d (%s)\n", err, evutil_socket_error_to_string(err));

    evconnlistener_free(listener);
}