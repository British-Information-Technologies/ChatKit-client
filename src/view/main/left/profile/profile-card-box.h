#ifndef VIEW_MAIN_LEFT_PROFILE_CARD_BOX_H_
#define VIEW_MAIN_LEFT_PROFILE_CARD_BOX_H_

#include "glibmm/refptr.h"
#include "gtkmm/box.h"
#include "gtkmm/builder.h"

class ProfileCardBox : public Gtk::Box {
private:
    const Glib::RefPtr<Gtk::Builder> refBuilder;

public:
    ProfileCardBox(
        BaseObjectType* cobject,
        const Glib::RefPtr<Gtk::Builder>& refBuilder);

    ~ProfileCardBox() = default;
};

#endif