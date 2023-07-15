#ifndef VIEW_INJECTOR_H_
#define VIEW_INJECTOR_H_

#include <functional>
#include <memory>
#include <gtkmm-4.0/gtkmm.h>

namespace view {
    class Injector {
        public:
            static std::shared_ptr<Gtk::ApplicationWindow> inject_login(
                std::function<void(int)> setViewState
            );

            static std::shared_ptr<Gtk::ApplicationWindow> inject_main();

        private:
            static int UpdateBuilder(
                const Glib::RefPtr<Gtk::Builder> &ref_builder,
                const std::string &filename
            );
    };
} // namespace view

#endif