#ifndef VIEW_MAIN_SHARED_CONTACT_LIST_BOX_H_
#define VIEW_MAIN_SHARED_CONTACT_LIST_BOX_H_

#include "glibmm/refptr.h"
#include "gtkmm/box.h"
#include "gtkmm/builder.h"
#include "gtkmm/button.h"
#include "gtkmm/scrolledwindow.h"

class ContactListBox : public Gtk::ScrolledWindow {
protected:
    const Glib::RefPtr<Gtk::Builder> refBuilder;

    const Glib::RefPtr<Gtk::Box> contact_box;

public:
    ContactListBox(
        BaseObjectType* cobject,
        const Glib::RefPtr<Gtk::Builder>& refBuilder,
        const Glib::RefPtr<Gtk::Box> contact_box);

    ~ContactListBox() = default;

    void AppendContactToList(Glib::RefPtr<Gtk::Widget> child);
};

#endif