#ifndef VIEW_MODEL_NETWORK_H_
#define VIEW_MODEL_NETWORK_H_

#include <gtkmm-4.0/gtkmm.h>
#include <memory>

#include "../model/network-model.h"

namespace view_model {
class NetworkViewModel {
private:
    std::shared_ptr<model::NetworkModel> model;

    // Bindings
    std::function<void()> showDirectMessage;

public:
    NetworkViewModel(
        std::shared_ptr<model::NetworkModel> model,
        std::function<void()> showDirectMessage);

    void SendMessageObserver(std::string& data);

    void OpenContactObserver();
};
} // namespace view_model

#endif