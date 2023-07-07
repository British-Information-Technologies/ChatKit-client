#ifndef VIEW_MODEL_ACCOUNT_H_
#define VIEW_MODEL_ACCOUNT_H_

#include <gtkmm-4.0/gtkmm.h>
#include <functional>

namespace view_model {
  class AccountViewModel {
    private:
      // Bindings
      std::function<void(int)> setViewState;

    public:
      AccountViewModel(
        std::function<void(int)> setViewState
      );

      void LoginObserver();
  };
}  // namespace view_model

#endif