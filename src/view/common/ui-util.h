#ifndef VIEW_COMMON_UI_UTIL_H_
#define VIEW_COMMON_UI_UTIL_H_

#include <gtkmm-4.0/gtkmm.h>
#include <string.h>

namespace view {
int UpdateBuilder(
    const Glib::RefPtr<Gtk::Builder>& ref_builder,
    const std::string& filename);
} // namespace view

#endif