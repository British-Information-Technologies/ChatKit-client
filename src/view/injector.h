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

    static std::shared_ptr<Gtk::Button> inject_friend_profile_card(
        std::shared_ptr<view_model::NetworkViewModel> network_vm,
        const std::string& uuid);

    static std::shared_ptr<Gtk::Button> inject_server_profile_card(
        std::shared_ptr<view_model::NetworkViewModel> network_vm);

private:
    static int UpdateBuilder(
        const Glib::RefPtr<Gtk::Builder>& ref_builder,
        const std::string& filename);
};
} // namespace view

#endif