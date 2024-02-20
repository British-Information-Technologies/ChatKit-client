#ifndef VIEW_MODEL_NETWORK_H_
#define VIEW_MODEL_NETWORK_H_

#include <gtkmm-4.0/gtkmm.h>
#include <memory>

#include "model/network-model.h"
#include "view/observers/notifications/notification-observer.h"

namespace view_model {
class NetworkViewModel {
private:
    std::unique_ptr<model::NetworkModel> model;

public:
    NetworkViewModel(
        std::unique_ptr<model::NetworkModel> model);

    void ConnectToServer(
        const std::string& ip_address,
        const std::string& port,
        view::NotificationObserver* notification);

    void ConnectToClient(
        const std::string& ip_address,
        const std::string& port,
        view::NotificationObserver* notification);

    int SendMessage(const std::string& uuid, const std::string& data);
};
} // namespace view_model

#endif