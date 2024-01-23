#ifndef VIEW_MAIN_RIGHT_ADD_SERVER_BOX_H_
#define VIEW_MAIN_RIGHT_ADD_SERVER_BOX_H_

#include <functional>
#include <gtkmm-4.0/gtkmm.h>

#include "view-model/network-view-model.h"

#define ADD_SERVER_TYPE add_server_get_type()

G_DECLARE_FINAL_TYPE(AddServer, add_server, ADD, SERVER, GtkBox)

static void add_server_dispose(GObject* gobject);

static void add_server_class_init(AddServerClass* klass);

static void add_server_init(AddServer* self);

void set_server_code_entry(std::shared_ptr<view_model::NetworkViewModel> network_vm);

void set_join_button(std::function<void()> func);

#endif