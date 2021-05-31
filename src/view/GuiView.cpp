#include "GuiView.h"

#include <gtk/gtk.h>

using namespace chat_client_view;

GuiView::GuiView(int argc, char **argv) {
    this->initalised = false;
    this->argc = argc;
    this->argv = argv;
}

void GuiView::menu() {
}

View * GuiView::getInstance(int argc, char **argv) {
    if(!initalised) {
        struct arguments args = {argc, argv};

        int threadStatus = this->startInternalThread();

        if(threadStatus) {
            return instance;
        }

        while(!initalised);
    }
    
    return instance;
}

void GuiView::internalThreadEntry() {
    GtkBuilder *builder; 
    GtkWidget *window;

    gtk_init(&this->argc, &this->argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "resources/mickyb18-chat-client.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(builder);

    this->instance = this;
    this->initalised = true;

    gtk_widget_show(window);                
    gtk_main();
    
    pthread_exit(NULL);
}

extern "C" {
    void on_main_window_destroy() {
        gtk_main_quit();
    }
}