#ifndef VIEW_OBSERVERS_WORKERS_SEND_MESSAGE_H_
#define VIEW_OBSERVERS_WORKERS_SEND_MESSAGE_H_

#include "glibmm/refptr.h"
#include "view-model/network-view-model.h"
#include "view/observers/workers/worker-observer.h"

#include <memory>
#include <string>

namespace view {
class SendMessageWorkerObserver : public WorkerObserver {
private:
    std::shared_ptr<view_model::NetworkViewModel> network_vm;

public:
    SendMessageWorkerObserver(
        std::shared_ptr<view_model::NetworkViewModel> network_vm);

    void Execute(const std::string& data);
};
} // namespace view

#endif