#include <gtkmm-4.0/gtkmm.h>

#define PROFILE_CARD_TYPE profile_card_get_type()

struct _ProfileCard {
    GtkBox parent_type;
};

G_DECLARE_FINAL_TYPE(ProfileCard, profile_card, PROFILE, CARD, GtkBox)
G_DEFINE_TYPE(ProfileCard, profile_card, GTK_TYPE_BOX)

static void profile_card_dispose(GObject *gobject) {
    gtk_widget_dispose_template(GTK_WIDGET(gobject), PROFILE_CARD_TYPE);
    
    G_OBJECT_CLASS(profile_card_parent_class)->dispose(gobject);
}

static void profile_card_class_init(ProfileCardClass *klass) {
    G_OBJECT_CLASS(klass)->dispose = profile_card_dispose;

    GtkWidgetClass *widget_class = GTK_WIDGET_CLASS(klass);
    
    gtk_widget_class_set_template_from_resource(
        widget_class,
        "/view/res/profile_card.ui"
    );

    // bind widgets inside template file to class members
    // gtk_widget_class_bind_template_child();
}

static void profile_card_init(ProfileCard *self) {
    gtk_widget_init_template(GTK_WIDGET(self));

    // It is now possible to access self->entry and self->button
}