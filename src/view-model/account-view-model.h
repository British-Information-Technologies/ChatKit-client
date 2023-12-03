#ifndef VIEW_MODEL_ACCOUNT_H_
#define VIEW_MODEL_ACCOUNT_H_

#include <functional>
#include <gtkmm-4.0/gtkmm.h>

namespace view_model {
class AccountViewModel {
private:
    // Bindings
    std::function<void(int)> setViewState;

public:
    AccountViewModel(
        std::function<void(int)> setViewState);

    void LoginObserver();
};
}// namespace view_model

#endif