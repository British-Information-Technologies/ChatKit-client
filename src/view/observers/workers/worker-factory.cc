#include "worker-factory.h"

#include <memory>

#include "view-model/network-view-model.h"
#include "view/observers/workers/send-message-worker-observer.h"

using namespace view;

WorkerObserver* view::GetWorker(
    WorkerType type,
    std::shared_ptr<view_model::NetworkViewModel> network_vm) {
    switch (type) {
    case WorkerType::SendMessage: {
        return new SendMessageWorkerObserver(network_vm);
    }
    default:
        return nullptr;
    }
}
