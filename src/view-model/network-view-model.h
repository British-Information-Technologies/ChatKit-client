#ifndef VIEW_MODEL_NETWORK_H_
#define VIEW_MODEL_NETWORK_H_

#include "../model/network-model.h"

namespace view_model {
  class NetworkViewModel {
    private:
      std::shared_ptr<model::NetworkModel> model;

    public:
      NetworkViewModel();

      void Main(int argc, char **argv);
  };
}  // namespace view_model

#endif