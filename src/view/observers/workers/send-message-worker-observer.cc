#include "send-message-worker-observer.h"

#include "view-model/network-view-model.h"
#include "view/observers/workers/worker-observer.h"

#include <iostream>
#include <memory>
#include <string>

using namespace view;

SendMessageWorkerObserver::SendMessageWorkerObserver(
    std::shared_ptr<view_model::NetworkViewModel> network_vm)
    : WorkerObserver(),
      network_vm(network_vm) {}

void SendMessageWorkerObserver::Execute(const std::string& data) {
    if (data.empty()) {
        return;
    }

    std::cout << "Message to send: " << data << std::endl;

    const std::string uuid = "faked uuid"; // TODO: faked

    network_vm->SendMessage(uuid, data);
}