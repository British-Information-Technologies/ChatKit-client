#ifndef VIEW_MAIN_LEFT_SERVER_LIST_BOX_H_
#define VIEW_MAIN_LEFT_SERVER_LIST_BOX_H_

#include "glibmm/refptr.h"
#include "gtkmm/box.h"
#include "gtkmm/builder.h"
#include "gtkmm/button.h"

#include "gtkmm/widget.h"
#include "view/main/shared/contact-list-box.h"
#include "view/main/shared/list-box.h"

class ServerListBox : public Gtk::Box, public ListBox {
private:
    const Glib::RefPtr<Gtk::Builder> refBuilder;

    const Glib::RefPtr<Gtk::Button> add_server_button;

    const Glib::RefPtr<ContactListBox> contact_list_box;

public:
    ServerListBox(
        BaseObjectType* cobject,
        const Glib::RefPtr<Gtk::Builder>& refBuilder,
        const Glib::RefPtr<Gtk::Button> add_server_button,
        const Glib::RefPtr<ContactListBox> contact_list_box);

    ~ServerListBox() = default;

    void AppendToList(ListType type, const Glib::RefPtr<Gtk::Widget> child);
};

#endif