#include <gtkmm-4.0/gtkmm.h>

#define HOME_PAGE_TYPE home_page_get_type()

struct _HomePage {
    GtkBox parent_type;
};

G_DECLARE_FINAL_TYPE(HomePage, home_page, HOME, PAGE, GtkBox)
G_DEFINE_TYPE(HomePage, home_page, GTK_TYPE_BOX)

static void home_page_dispose(GObject* gobject) {
    gtk_widget_dispose_template(GTK_WIDGET(gobject), HOME_PAGE_TYPE);

    G_OBJECT_CLASS(home_page_parent_class)->dispose(gobject);
}

static void home_page_class_init(HomePageClass* klass) {
    G_OBJECT_CLASS(klass)->dispose = home_page_dispose;

    GtkWidgetClass* widget_class = GTK_WIDGET_CLASS(klass);

    gtk_widget_class_set_template_from_resource(
        widget_class,
        "/view/res/homepage.ui");

    // bind widgets inside template file to class members
    // gtk_widget_class_bind_template_child();
}

static void home_page_init(HomePage* self) {
    gtk_widget_init_template(GTK_WIDGET(self));

    // It is now possible to access self->entry and self->button
}