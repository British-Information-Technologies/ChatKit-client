#ifndef MODEL_NETWORKING_UTILITY_SECURE_DATA_HANDLER_H_
#define MODEL_NETWORKING_UTILITY_SECURE_DATA_HANDLER_H_

#include <memory>
#include <string>

#include "data-handler.h"

namespace model {
class SecureDataHandler : public DataHandler {
 private:
  DataHandlerType type = DataHandlerType::Secure;

  std::unique_ptr<unsigned char[]> ss;

 public:
  SecureDataHandler(unsigned char *ss);

  DataHandlerType GetType();

  std::string FormatSend(std::string &data);
  std::string FormatRead(std::string &data);
};
}  // namespace model_networking_utility

#endif