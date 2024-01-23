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

#include "tunnel.h"

#include "model/networking/connection/tunnel/data-handler/data-handler.h"
#include "model/networking/connection/tunnel/data-handler/insecure-data-handler.h"
#include "model/networking/connection/tunnel/data-handler/secure-data-handler.h"
#include "model/networking/utility/encode.h"

#include "model/networking/messages/internal/event-error.h"
#include "model/networking/messages/message.h"

#include "model/networking/connection/callback/io-callbacks.h"

using namespace model;

// get sockaddr, IPv4 or IPv6:
void* Tunnel::GetInAddr(struct sockaddr* sa) {
    return &(((struct sockaddr_in*)sa)->sin_addr);
}

std::tuple<unsigned char*, unsigned char*> Tunnel::GenerateKeyPair() {
    // ensures operations are thread safe
    if (sodium_init() < 0) {
        // sodium initialisation failed
        return std::make_tuple(nullptr, nullptr);
    }

    // generate keypair
    unsigned char public_key[crypto_kx_PUBLICKEYBYTES];
    unsigned char secret_key[crypto_kx_SECRETKEYBYTES];

    if (crypto_kx_keypair(public_key, secret_key) != 0) {
        // keypair generation failed
        return std::make_tuple(nullptr, nullptr);
    }

    return std::make_tuple(public_key, secret_key);
}

void Tunnel::SetState(DataHandler* next_handler) {
    data_handler.reset(next_handler);
}

void Tunnel::SetBev(bufferevent* bev) {
    this->bev.reset(
        bev,
        [](bufferevent* b) {
            bufferevent_free(b);
        });
}

int Tunnel::EnableBuffer() {
    if (bufferevent_enable(bev.get(), EV_READ | EV_WRITE) != 0) {
        // panic! failed to enable event socket read and write
        return -1;
    }

    return 0;
}

const char* Tunnel::GetIpAddress() {
    return ip_address.c_str();
}

int Tunnel::GetPort() {
    return std::stoi(port);
}

Tunnel::Tunnel(
    const TunnelType type,
    std::shared_ptr<Connection> connection,
    std::shared_ptr<event_base> base,
    const std::string& ip_address,
    const std::string& port) : type(type),
                               connection(connection),
                               ip_address(ip_address),
                               port(port),
                               data_handler(new InsecureDataHandler) {
    auto [public_key, secret_key] = GenerateKeyPair();

    this->public_key.reset(public_key);
    this->secret_key.reset(secret_key);

    this->bev.reset(bufferevent_socket_new(base.get(), -1, BEV_OPT_CLOSE_ON_FREE),
                    [](bufferevent* b) {
                        bufferevent_free(b);
                    });
}

bool Tunnel::IsSecure() {
    return data_handler->GetType() == DataHandlerType::Secure;
}

const TunnelType Tunnel::GetType() {
    return type;
}

const std::string Tunnel::GetPublicKey() {
    return Bin2Base64(public_key.get(), crypto_kx_PUBLICKEYBYTES);
}

int Tunnel::Initiate() {
    if (!bev.get()) {
        // panic! failed to create connection - bev is null
        return -1;
    }

    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET_ADDRSTRLEN]; // add a 6 to INET to make it work with ivp 6 - remove 6 for ivp 4

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET; // add a 6 to make it work with ivp 6 - remove 6 for ivp 4
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    if ((rv = getaddrinfo(ip_address.c_str(), port.c_str(), &hints, &servinfo)) != 0) {
        fprintf(stderr, "[Tunnel]: getaddrinfo = %s\n", gai_strerror(rv));
        return -1;
    }

    // loop through all the results and connect to the first we can
    int sockfd;
    fd_set fdset;
    struct timeval tv;
    p = servinfo;

    while (p != nullptr) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            printf("[Tunnel]: socket creation failed\n");
            continue;
        }

        bufferevent_setfd(bev.get(), sockfd);

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
            if (so_error) {
                close(sockfd);
                bufferevent_free(bev.get());
                perror("[Tunnel]: open socket failed\n");
            }

            break;
        }

        p = p->ai_next;
    }

    if (!p) {
        fprintf(stderr, "[Tunnel]: failed to connect\n");
        return -1;
    }

    inet_ntop(p->ai_family, GetInAddr((struct sockaddr*)p->ai_addr), s, sizeof s);

    printf("[Tunnel]: connecting to %s\n", s);

    freeaddrinfo(servinfo); // all done with this structure

    switch (GetType()) {
    case TunnelType::Client:
        model_networking_connection_callback::SetClientConnectionCallbacks(bev.get(), connection.get());
        break;

    case TunnelType::Server:
        model_networking_connection_callback::SetServerConnectionCallbacks(bev.get(), connection.get());
    }

    SetState(new InsecureDataHandler());

    return 0;
}

int Tunnel::EstablishSecureTunnel(Party party, const unsigned char* recv_pk) {
    // ensures operations are thread safe
    if (sodium_init() < 0) {
        // sodium initialisation failed
        return -1;
    }

    // create shared secret with recipient PK and our SK
    unsigned char session_key_rx[crypto_kx_SESSIONKEYBYTES];
    unsigned char session_key_tx[crypto_kx_SESSIONKEYBYTES];

    int res = (party == Party::One) ? crypto_kx_server_session_keys(
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
        return -1;
    }

    SetState(new SecureDataHandler(session_key_rx, session_key_tx));

    return 0;
}

std::string Tunnel::ReadMessage(std::string& data) {
    return data_handler->FormatRead(data);
}
