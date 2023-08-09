#ifndef VIEW_MAIN_RIGHT_DIRECT_MESSAGE_BOX_H_
#define VIEW_MAIN_RIGHT_DIRECT_MESSAGE_BOX_H_

#include <gtkmm-4.0/gtkmm.h>
#include <functional>

#define DIRECT_MESSAGE_TYPE direct_message_get_type()

G_DECLARE_FINAL_TYPE(DirectMessage, direct_message, DIRECT, MESSAGE, GtkBox)

static void direct_message_dispose(GObject *gobject);

static void direct_message_class_init(DirectMessageClass *klass);

static void direct_message_init(DirectMessage *self);

void set_message_entry(std::function<void()> func);

#endif