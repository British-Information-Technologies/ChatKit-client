#ifndef VIEW_OBSERVERS_WORKERS_H_
#define VIEW_OBSERVERS_WORKERS_H_

#include <string>

namespace view {
class WorkerObserver {
public:
    virtual ~WorkerObserver() = default;

    virtual void Execute(const std::string& data) = 0;
};
} // namespace view

#endif