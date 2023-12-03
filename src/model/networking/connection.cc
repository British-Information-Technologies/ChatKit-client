#include "msd/channel.hpp"
#include <algorithm>
#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <event2/bufferevent.h>
#include <event2/event.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <fcntl.h>
#include <iostream>
#include <memory>
#include <netdb.h>
#include <sodium.h>
#include <string>
#include <sys/select.h>

#include "connection.h"

#include "utility/data-handler.h"
#include "utility/encode.h"
#include "utility/insecure-data-handler.h"
#include "utility/secure-data-handler.h"

#include "messages/internal/event-error.h"
#include "messages/message.h"

using namespace model;

// get sockaddr, IPv4 or IPv6:
void* Connection::GetInAddr(struct sockaddr* sa) {
    return &(((struct sockaddr_in*)sa)->sin_addr);
}

std::tuple<unsigned char*, unsigned char*> Connection::GenerateKeyPair() {
    // ensures operations are thread safe
    if (sodium_init() < 0) {
        // sodium initialisation failed
        return std::make_tuple(nullptr, nullptr);
    }

    // generate keypair
    unsigned char* public_key = (unsigned char*)malloc(sizeof(unsigned char[crypto_kx_PUBLICKEYBYTES]));
    unsigned char* secret_key = (unsigned char*)malloc(sizeof(unsigned char[crypto_kx_SECRETKEYBYTES]));

    if (crypto_kx_keypair(public_key, secret_key) != 0) {
        // keypair generation failed
        free(public_key);
        free(secret_key);

        return std::make_tuple(nullptr, nullptr);
    }

    return std::make_tuple(public_key, secret_key);
}

void Connection::SetState(DataHandler* next_handler) {
    data_handler.reset(next_handler);
}

void Connection::SendChannelMessage(std::shared_ptr<Message> message) {
    std::move(Data{uuid, bufferevent_getfd(bev.get()), message}) >> out_chann;
}

Connection::Connection(
    const std::string& uuid,
    std::shared_ptr<event_base> base,
    msd::channel<Data>& network_manager_chann,
    const std::string& ip_address,
    const std::string& port,
    unsigned char* public_key,
    unsigned char* secret_key) : uuid(uuid),
                                 out_chann(network_manager_chann),
                                 ip_address(ip_address),
                                 port(port),
                                 data_handler(new InsecureDataHandler),
                                 public_key(public_key),
                                 secret_key(secret_key),
                                 listener(nullptr),
                                 is_listener(0) {
    this->bev.reset(bufferevent_socket_new(base.get(), -1, BEV_OPT_CLOSE_ON_FREE),
                    [](bufferevent* b) {
                        bufferevent_free(b);
                    });
}

Connection::~Connection() {
    if (listener != nullptr) {
        evconnlistener_free(listener);
    }
}

bool Connection::IsSecure() {
    return data_handler->GetType() == DataHandlerType::Secure;
}

const std::string Connection::GetPublicKey() {
    return Bin2Base64(public_key.get(), crypto_kx_PUBLICKEYBYTES);
}

int Connection::Initiate() {
    if (!bev.get()) {
        // panic! failed to create connection - bev is null
        return -1;
    }

    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET_ADDRSTRLEN];// add a 6 to INET to make it work with ivp 6 - remove 6 for ivp 4

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;// add a 6 to make it work with ivp 6 - remove 6 for ivp 4
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    if ((rv = getaddrinfo(ip_address.c_str(), port.c_str(), &hints, &servinfo)) != 0) {
        fprintf(stderr, "[Connection]: getaddrinfo = %s\n", gai_strerror(rv));
        return -1;
    }

    // loop through all the results and connect to the first we can
    int sockfd;
    fd_set fdset;
    struct timeval tv;
    p = servinfo;

    while (p != nullptr) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            printf("[Connection]: socket creation failed\n");
            continue;
        }

        // Set the socket that the `connect` syscall to non-blocking
        // F_SETFL will set status flag for the file descriptor
        // and O_NONBLOCK is not block
        fcntl(sockfd, F_SETFL, O_NONBLOCK);
        connect(sockfd, p->ai_addr, p->ai_addrlen);

        // Clear the set of file descriptors and include the current socket
        FD_ZERO(&fdset);
        FD_SET(sockfd, &fdset);
        // set timeout in sec and microsec
        tv.tv_sec = 1;
        tv.tv_usec = 50;

        // `select` will return whenever any file descriptor in the set is writeable from the connect function (or ready for any other I/O operations),
        // we have a `timevalue` struct given to define a timeout.
        if (select(sockfd + 1, NULL, &fdset, NULL, &tv) != 0) {
            int so_error;
            socklen_t len = sizeof so_error;
            // get the socket options to determine outcome of `select`.
            // SOL_SOCKET defines the level to be options at API level
            // and SO_ERROR is here to look if the socket errored,
            // set the so_error option value.
            getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &so_error, &len);
            // if we timeout, then `select` has set this option
            // in the socket file descriptors options.
            std::cout << "hi" << std::endl;
            if (so_error) {
                close(sockfd);
                perror("[Connection]: open socket failed\n");
                break;
            }
        }

        p = p->ai_next;
    }

    if (p == nullptr) {
        fprintf(stderr, "[Connection]: failed to connect\n");
        return -1;
    }

    inet_ntop(p->ai_family, GetInAddr((struct sockaddr*)p->ai_addr), s, sizeof s);

    printf("[Connection]: connecting to %s\n", s);

    freeaddrinfo(servinfo);// all done with this structure

    bufferevent_setfd(bev.get(), sockfd);

    bufferevent_setcb(bev.get(), ReadMessageCbHandler, WriteMessageCbHandler, EventCbHandler, this);

    if (bufferevent_enable(bev.get(), EV_READ | EV_WRITE) != 0) {
        // panic! failed to enable event socket read and write
        return -1;
    }

    SetState(new InsecureDataHandler());

    return 0;
}

/* TODO: most likely will need to be moved to NetworkManager, rather than per Connection.
 *       this is to handle multiple Connections requesting to connect. */
void Connection::Listen(std::shared_ptr<event_base> base) {
    struct sockaddr_in sin;

    // Clear the sockaddr in case extra platform-specific fields are messed up
    memset(&sin, 0, sizeof(sin));

    sin.sin_family = AF_INET;// add 6 for ipv6

    sin.sin_addr.s_addr = htonl(0);       // listen on 0.0.0.0
    sin.sin_port = htons(std::stoi(port));// listen on port

    listener = evconnlistener_new_bind(
        base.get(),
        AcceptConnectionCbHandler,
        this,
        LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE,
        -1,
        (struct sockaddr*)&sin,
        sizeof(sin));

    SetIsListener(1);
    evconnlistener_set_error_cb(listener, AcceptErrorCbHandler);

    printf("[Connection]: listener started\n");
}

int Connection::EstablishSecureConnection(const unsigned char* recv_pk) {
    // ensures operations are thread safe
    if (sodium_init() < 0) {
        // sodium initialisation failed
        return -1;
    }

    // create shared secret with recipient PK and our SK
    unsigned char* session_key_rx = (unsigned char*)malloc(sizeof(unsigned char[crypto_kx_SESSIONKEYBYTES]));
    unsigned char* session_key_tx = (unsigned char*)malloc(sizeof(unsigned char[crypto_kx_SESSIONKEYBYTES]));

    int res = (is_listener) ? crypto_kx_server_session_keys(
                  session_key_rx,
                  session_key_tx,
                  public_key.get(),
                  secret_key.get(),
                  recv_pk)
                            : crypto_kx_client_session_keys(
                                session_key_rx,
                                session_key_tx,
                                public_key.get(),
                                secret_key.get(),
                                recv_pk);

    if (res) {
        // shared secret creation failed
        free(session_key_rx);
        free(session_key_tx);

        return -1;
    }

    SetState(new SecureDataHandler(session_key_rx, session_key_tx));

    return 0;
}

void Connection::SetIsListener(int state) {
    is_listener = state;
}

void Connection::AcceptConnectionCbHandler(
    struct evconnlistener* listener,
    evutil_socket_t sockfd,
    struct sockaddr* address,
    int socklen,
    void* ptr) {
    Connection* conn = static_cast<Connection*>(ptr);
    conn->AcceptConnectionCb(sockfd, address);
}

void Connection::AcceptConnectionCb(evutil_socket_t sockfd, struct sockaddr* address) {
    // we got a new connection, free the listener
    evconnlistener_free(listener);

    // set the socket fd for the connection bufferevent
    bufferevent_setfd(bev.get(), sockfd);

    // set connection callbacks
    bufferevent_setcb(bev.get(), ReadMessageCbHandler, WriteMessageCbHandler, EventCbHandler, this);

    // enable the bufferevent read and write
    if (bufferevent_enable(bev.get(), EV_READ | EV_WRITE) != 0) {
        // panic! failed to enable event socket read and write
        return;
    }

    std::cout << "[Connection]: connecting to " << ip_address << std::endl;
}

void Connection::AcceptErrorCbHandler(struct evconnlistener* listener, void* ptr) {
    Connection* conn = static_cast<Connection*>(ptr);
    conn->AcceptErrorCb();
}

void Connection::AcceptErrorCb() {
    int err = EVUTIL_SOCKET_ERROR();

    fprintf(stderr, "[Connection]: listener error = %d (%s)\n", err, evutil_socket_error_to_string(err));

    evconnlistener_free(listener);
}

void Connection::ReadMessageCbHandler(struct bufferevent* bev, void* ptr) {
    Connection* conn = static_cast<Connection*>(ptr);
    conn->ReadMessageCb();
}

void Connection::WriteMessageCbHandler(struct bufferevent* bev, void* ptr) {
    Connection* conn = static_cast<Connection*>(ptr);
    conn->WriteMessageCb();
}

void Connection::WriteMessageCb() {
    printf("[Connection]: data successfully written to socket\n");
}

void Connection::EventCbHandler(struct bufferevent* bev, short events, void* ptr) {
    Connection* conn = static_cast<Connection*>(ptr);
    conn->EventCb(events);
}

void Connection::EventCb(short events) {
    if (events && (BEV_EVENT_ERROR || BEV_EVENT_READING || BEV_EVENT_WRITING)) {
        printf("[Connection]: buffer event error, terminating connection!\n");

        /* send data to network manager - todo add message factory
    json data = {
      { "sockfd", bufferevent_getfd(bev.get()) },
      { "internal", internal::EventError("Buffer Event Error! Terminating Connection!").Serialize() },
    };

    bufferevent_free(bev.get());
    
    data >> out_chann;*/
    }
}
