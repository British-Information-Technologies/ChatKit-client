#ifndef MODEL_NETWORKING_UTILITY_DATA_HANDLER_H_
#define MODEL_NETWORKING_UTILITY_DATA_HANDLER_H_

#include <string>

namespace model {
  class DataHandler {
    public:
      virtual std::string FormatSend(std::string &data) = 0;
      virtual std::string FormatRead(std::string &data) = 0;
  };
}  // namespace model_networking_utility

#endif