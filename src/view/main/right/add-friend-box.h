#ifndef VIEW_MAIN_RIGHT_ADD_FRIEND_BOX_H_
#define VIEW_MAIN_RIGHT_ADD_FRIEND_BOX_H_

#include <functional>
#include <gtkmm-4.0/gtkmm.h>

#define ADD_FRIEND_TYPE add_friend_get_type()

G_DECLARE_FINAL_TYPE(AddFriend, add_friend, ADD, FRIEND, GtkBox)

static void add_friend_dispose(GObject* gobject);

static void add_friend_class_init(AddFriendClass* klass);

static void add_friend_init(AddFriend* self);

void set_friend_code_entry(/*TODO: std::function<void()> func*/);

void set_send_invite_button(std::function<void()> func);

#endif