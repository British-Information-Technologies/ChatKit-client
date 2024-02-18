#include "home-page-box.h"

#include "glibmm/refptr.h"
#include "gtkmm/box.h"
#include "gtkmm/builder.h"

HomePage::HomePage(
    BaseObjectType* cobject,
    const Glib::RefPtr<Gtk::Builder>& refBuilder)
    : Glib::ObjectBase("HomePage"), Gtk::Box(cobject), refBuilder(refBuilder) {}