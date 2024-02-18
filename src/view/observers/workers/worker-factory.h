#ifndef VIEW_OBSERVERS_WORKERS_FACTORY_H_
#define VIEW_OBSERVERS_WORKERS_FACTORY_H_

#include <memory>

#include "view-model/network-view-model.h"
#include "view/observers/workers/worker-observer.h"

namespace view {
enum class WorkerType {
    SendMessage,
};

WorkerObserver* GetWorker(
    WorkerType type,
    std::shared_ptr<view_model::NetworkViewModel> network_vm);
} // namespace view

#endif
