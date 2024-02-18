#ifndef VIEW_MAIN_LEFT_PROFILE_INJECTOR_H_
#define VIEW_MAIN_LEFT_PROFILE_INJECTOR_H_

#include "glibmm/refptr.h"
#include "view/main/left/profile/profile-card-box.h"

namespace injector {
const Glib::RefPtr<ProfileCardBox> inject_profile_card_box();
} // namespace injector

#endif