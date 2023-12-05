#ifndef MODEL_INJECTOR_H_
#define MODEL_INJECTOR_H_

#include <memory>

#include "data-model.h"
#include "network-model.h"

namespace model {
class Injector {
public:
    static std::shared_ptr<DataModel> inject_data_model();
    static std::shared_ptr<NetworkModel> inject_network_model();
};
} // namespace model

#endif