#ifndef CLIENT_CONTROLLER_H
#define CLIENT_CONTROLLER_H

#include "../view/View.h"

using namespace chat_client_view;

namespace chat_client_controller {
    class ClientController {
        private:
            View * view;

        public:
            ClientController(int, char**);
    };
}

#endif