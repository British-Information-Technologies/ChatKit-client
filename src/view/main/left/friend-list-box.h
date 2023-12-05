#ifndef VIEW_MAIN_LEFT_FRIEND_LIST_H_
#define VIEW_MAIN_LEFT_FRIEND_LIST_H_

#include <functional>
#include <gtkmm-4.0/gtkmm.h>

#define FRIEND_LIST_TYPE friend_list_get_type()

G_DECLARE_FINAL_TYPE(FriendList, friend_list, FRIEND, LIST, GtkBox)

static void friend_list_dispose(GObject* gobject);

static void friend_list_class_init(FriendListClass* klass);

static void friend_list_init(FriendList* self);

void set_add_friend_button(std::function<void()> func);

void append_friend_to_list(Glib::RefPtr<Gtk::Widget> child);

#endif