#ifndef VIEW_MAIN_RIGHT_HOMEPAGE_BOX_H_
#define VIEW_MAIN_RIGHT_HOMEPAGE_BOX_H_

#include "glibmm/refptr.h"
#include "gtkmm/box.h"
#include "gtkmm/builder.h"

class HomePage : public Gtk::Box {
private:
    const Glib::RefPtr<Gtk::Builder> refBuilder;

public:
    HomePage(
        BaseObjectType* cobject,
        const Glib::RefPtr<Gtk::Builder>& refBuilder);

    ~HomePage() = default;
};

#endif