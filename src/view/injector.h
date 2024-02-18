#ifndef VIEW_INJECTOR_H_
#define VIEW_INJECTOR_H_

#include <functional>
#include <gtkmm-4.0/gtkmm.h>
#include <memory>

#include "view-model/network-view-model.h"

namespace view {
class Injector {
public:
    static std::shared_ptr<Gtk::ApplicationWindow> inject_login(
        std::function<void(int)> setViewState);

    static std::shared_ptr<Gtk::ApplicationWindow> inject_main();
};
} // namespace view

#endif