#ifndef VIEW_FACTORY_H
#define VIEW_FACTORY_H

#include "../view/View.h"

namespace chat_client_controller {
    class ViewFactory {
        public:
            chat_client_view::View * createView(int, char**);
    };
}

#endif