#ifndef GUI_VIEW_H
#define GUI_VIEW_H

#include "../view/View.h"

#include <pthread.h>
#include <gtk/gtk.h>

namespace chat_client_view {
    class GuiView: View {
        private:
            GuiView *instance;
            bool initalised;
            int argc;
            char **argv;

            void start();

        public:
            GuiView(int argc, char **argv);

            void menu();

            View * getInstance(int, char**);
        
        protected:
            void internalThreadEntry();
    };
}

struct arguments {
    int argc;
    char **argv;
};

#endif