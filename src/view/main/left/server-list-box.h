#ifndef VIEW_MAIN_LEFT_SERVER_LIST_H_
#define VIEW_MAIN_LEFT_SERVER_LIST_H_

#include <gtkmm-4.0/gtkmm.h>

#define SERVER_LIST_TYPE server_list_get_type()

G_DECLARE_FINAL_TYPE(ServerList, server_list, SERVER, LIST, GtkBox)

static void server_list_dispose(GObject* gobject);

static void server_list_class_init(ServerListClass* klass);

static void server_list_init(ServerList* self);

void set_add_server_button(std::function<void()> func);

void append_server_to_list(Glib::RefPtr<Gtk::Widget> child);

#endif