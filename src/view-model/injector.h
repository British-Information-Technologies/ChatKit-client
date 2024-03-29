#ifndef VIEW_MODEL_INJECTOR_H_
#define VIEW_MODEL_INJECTOR_H_

#include <functional>
#include <gtkmm-4.0/gtkmm.h>
#include <memory>

#include "account-view-model.h"
#include "network-view-model.h"

namespace view_model {
class Injector {
public:
    static std::shared_ptr<AccountViewModel> inject_account_vm(
        std::function<void(int)> setViewState);

    static std::shared_ptr<NetworkViewModel> inject_network_vm(
        std::function<void()> showDirectMessage);
};
} // namespace view_model

#endif