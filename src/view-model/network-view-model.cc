#include <memory>
#include <string>

#include "network-view-model.h"

#include "../model/network-model.h"

using namespace view_model;
using namespace model;

NetworkViewModel::NetworkViewModel() {
  model = std::make_shared<NetworkModel>();
}

void NetworkViewModel::Main(int argc, char **argv) {
  model->Run();
}