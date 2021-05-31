#ifndef CLIENT_CONTROLLER_H
#define CLIENT_CONTROLLER_H

#include "../view/View.h"

namespace chat_client_controller {
    class ClientController {
        private:
            chat_client_view::View * view;

        public:
            ClientController(int, char**);
    };
}

#endif