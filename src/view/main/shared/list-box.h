#ifndef VIEW_MAIN_SHARED_LIST_BOX_H_
#define VIEW_MAIN_SHARED_LIST_BOX_H_

#include "glibmm/refptr.h"
#include "gtkmm/widget.h"

enum class ListType {
    Message,
    Contact,
};

class ListBox {
public:
    ~ListBox() = default;

    virtual void AppendToList(ListType type, const Glib::RefPtr<Gtk::Widget>) = 0;
};

#endif