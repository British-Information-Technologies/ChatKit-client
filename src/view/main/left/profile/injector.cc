#include "injector.h"

#include "glibmm/refptr.h"
#include "gtkmm/builder.h"
#include "view/common/ui-util.h"

#include "view/main/left/profile/profile-card-box.h"

const Glib::RefPtr<ProfileCardBox> injector::inject_profile_card_box() {
    Glib::RefPtr<Gtk::Builder> profile_card_builder = Gtk::Builder::create();

    view::UpdateBuilder(profile_card_builder, "/view/res/profile_card.ui");

    return Glib::RefPtr<ProfileCardBox>(profile_card_builder->get_widget_derived<ProfileCardBox>(profile_card_builder, "profileCardBox"));
}
