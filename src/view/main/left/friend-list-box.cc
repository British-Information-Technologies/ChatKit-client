#include <functional>
#include <gtkmm-4.0/gtkmm.h>
#include <list>

#include "friend-list-box.h"

struct _FriendList {
    GtkBox parent_type;

    GtkButton* addFriendButton;
    GtkBox* contactBox;
};

G_DEFINE_TYPE(FriendList, friend_list, GTK_TYPE_BOX)

static FriendList* friend_list;

static std::list<Glib::RefPtr<Gtk::Widget>> contacts;

static void friend_list_dispose(GObject* gobject) {
    gtk_widget_dispose_template(GTK_WIDGET(gobject), FRIEND_LIST_TYPE);

    G_OBJECT_CLASS(friend_list_parent_class)->dispose(gobject);
}

static void friend_list_class_init(FriendListClass* klass) {
    G_OBJECT_CLASS(klass)->dispose = friend_list_dispose;

    GtkWidgetClass* widget_class = GTK_WIDGET_CLASS(klass);

    gtk_widget_class_set_template_from_resource(
        widget_class,
        "/view/res/friend_list.ui");

    // bind widgets inside template file to class members
    gtk_widget_class_bind_template_child(widget_class, FriendList, addFriendButton);
    gtk_widget_class_bind_template_child(widget_class, FriendList, contactBox);
}

static void friend_list_init(FriendList* self) {
    gtk_widget_init_template(GTK_WIDGET(self));

    friend_list = self;

    // It is now possible to access self->attributes
}

void set_add_friend_button(std::function<void()> func) {
    Glib::wrap(friend_list->addFriendButton, true)->signal_clicked().connect(func);
}

void append_friend_to_list(Glib::RefPtr<Gtk::Widget> child) {
    gtk_box_append(
        friend_list->contactBox,
        child->gobj());

    contacts.push_back(child);
}