#include <functional>
#include <memory>

#include "injector.h"

#include "account-view-model.h"
#include "network-view-model.h"

#include "model/injector.h"
#include "model/network-model.h"

using namespace view_model;

std::shared_ptr<AccountViewModel> Injector::inject_account_vm(
    std::function<void(int)> setViewState) {
    std::shared_ptr<AccountViewModel> account_vm(
        new AccountViewModel(
            setViewState));

    return account_vm;
}

std::shared_ptr<NetworkViewModel> Injector::inject_network_vm(
    std::function<void()> showDirectMessage) {
    std::shared_ptr<model::NetworkModel> network_model = model::Injector::inject_network_model();

    std::shared_ptr<NetworkViewModel> network_vm(
        new NetworkViewModel(
            network_model,
            showDirectMessage));

    return network_vm;
}