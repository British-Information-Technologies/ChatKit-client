#include "server-connection.h"
#include <bits/stdc++.h>

using namespace networking_server; 

// get sockaddr, IPv4 or IPv6:
void *ServerConnection::get_in_addr(struct sockaddr *sa) {
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int ServerConnection::create_connection(std::string &ip_address, std::string &port) {
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET6;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    if ((rv = getaddrinfo((const char *)ip_address[0], (const char *)port[0], &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return -1;
    }

    // loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("client: connect");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        return -1;
    }

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), s, sizeof s);
    printf("client: connecting to %s\n", s);

    freeaddrinfo(servinfo); // all done with this structure

    return 1;
}

int ServerConnection::send_message(std::string &message) {
    return send(sockfd, (char *)message[0], sizeof(message), 0);
}

int ServerConnection::read_message(char *buffer, size_t buffer_size) {  
    int numbytes = recv(sockfd, buffer, buffer_size - 1, 0);

    *(buffer + buffer_size) = '\0';

    return numbytes;
}