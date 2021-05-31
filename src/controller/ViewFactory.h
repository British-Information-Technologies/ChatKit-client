#ifndef VIEW_FACTORY_H
#define VIEW_FACTORY_H

#include "../view/View.h"

using namespace chat_client_view;
namespace chat_client_controller {
    class ViewFactory {
        public:
            View * createView(int, char**);
    };
}

#endif