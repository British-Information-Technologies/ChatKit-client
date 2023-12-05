#include <functional>
#include <gtkmm-4.0/gtkmm.h>

#include "add-friend-box.h"

struct _AddFriend {
    GtkBox parent_type;

    GtkEntry* friendCodeEntry;
    GtkBox* addFriendProfileCardBox;
    GtkButton* sendInviteButton;
};

G_DEFINE_TYPE(AddFriend, add_friend, GTK_TYPE_BOX)

static AddFriend* add_friend;

namespace {
// TODO (eventually remove): faked for testing reasons
bool on_widget_key_pressed(guint keyval, guint _, Gdk::ModifierType state) {
    if (keyval == GDK_KEY_Return) {
        gtk_widget_set_visible(
            GTK_WIDGET(add_friend->addFriendProfileCardBox),
            true);
    }

    return false;
}
} // namespace

static void add_friend_dispose(GObject* gobject) {
    gtk_widget_dispose_template(GTK_WIDGET(gobject), ADD_FRIEND_TYPE);

    G_OBJECT_CLASS(add_friend_parent_class)->dispose(gobject);
}

static void add_friend_class_init(AddFriendClass* klass) {
    G_OBJECT_CLASS(klass)->dispose = add_friend_dispose;

    GtkWidgetClass* widget_class = GTK_WIDGET_CLASS(klass);

    gtk_widget_class_set_template_from_resource(
        widget_class,
        "/view/res/add_friend.ui");

    // bind widgets inside template file to class members
    gtk_widget_class_bind_template_child(widget_class, AddFriend, friendCodeEntry);
    gtk_widget_class_bind_template_child(widget_class, AddFriend, addFriendProfileCardBox);
    gtk_widget_class_bind_template_child(widget_class, AddFriend, sendInviteButton);
}

static void add_friend_init(AddFriend* self) {
    gtk_widget_init_template(GTK_WIDGET(self));

    add_friend = self;

    // It is now possible to access self->attributes
    set_friend_code_entry(); // TODO: will be removed
}

void set_friend_code_entry(/*TODO: std::function<void()> func (function to send network vm data) */) {
    auto event_ck = Gtk::EventControllerKey::create();

    event_ck->signal_key_pressed().connect(
        sigc::ptr_fun(&on_widget_key_pressed),
        false);

    Glib::wrap(GTK_WIDGET(add_friend), true)->add_controller(event_ck);
}

void set_send_invite_button(std::function<void()> func) {
    Glib::wrap(
        add_friend->sendInviteButton,
        true)
        ->signal_clicked()
        .connect(func);
}