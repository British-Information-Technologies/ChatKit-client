#include "profile-card-box.h"

#include "glibmm/refptr.h"
#include "gtkmm/box.h"
#include "gtkmm/builder.h"

ProfileCardBox::ProfileCardBox(
    BaseObjectType* cobject,
    const Glib::RefPtr<Gtk::Builder>& refBuilder)
    : Glib::ObjectBase("ProfileCardBox"),
      Gtk::Box(cobject),
      refBuilder(refBuilder) {}