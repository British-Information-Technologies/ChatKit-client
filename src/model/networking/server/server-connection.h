#ifndef CPPCHATCLIENT_MODEL_CLIENTMODEL_
#define CPPCHATCLIENT_MODEL_CLIENTMODEL_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <arpa/inet.h>

namespace networking_server {
    class ServerConnection {
        private:
            int sockfd;

        private:
            void *get_in_addr(struct sockaddr *);


        public:
            int create_connection(std::string &, std::string &);
            int send_message(std::string &);
            int read_message(char *, size_t);
    };
}

#endif