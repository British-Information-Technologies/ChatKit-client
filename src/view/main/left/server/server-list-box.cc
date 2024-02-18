#include "server-list-box.h"

#include "glibmm/refptr.h"
#include "gtkmm/box.h"
#include "gtkmm/builder.h"
#include "gtkmm/button.h"
#include "view/main/left/shared/contact-list-box.h"

ServerListBox::ServerListBox(
    BaseObjectType* cobject,
    const Glib::RefPtr<Gtk::Builder>& refBuilder,
    const Glib::RefPtr<Gtk::Button> add_server_button)
    : ContactListBox(
        cobject,
        "ServerListBox",
        refBuilder,
        add_server_button,
        refBuilder->get_object<Gtk::Box>("contactBox")) {}
