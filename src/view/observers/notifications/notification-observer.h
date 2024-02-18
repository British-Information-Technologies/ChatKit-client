#ifndef VIEW_OBSERVERS_NOTIFICATIONS_H_
#define VIEW_OBSERVERS_NOTIFICATIONS_H_

#include <string>

namespace view {
class NotificationObserver {
public:
    virtual ~NotificationObserver() = default;

    virtual void Notify(const std::string& alias, const std::string& owner) = 0;
};
} // namespace view

#endif