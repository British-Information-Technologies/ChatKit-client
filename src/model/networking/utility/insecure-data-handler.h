#ifndef MODEL_NETWORKING_UTILITY_INSECURE_DATA_HANDLER_H_
#define MODEL_NETWORKING_UTILITY_INSECURE_DATA_HANDLER_H_

#include <string>

#include "data-handler.h"

namespace model {
class InsecureDataHandler : public DataHandler {
private:
    DataHandlerType type = DataHandlerType::Insecure;

public:
    DataHandlerType GetType();

    std::string FormatSend(std::string& data);
    std::string FormatRead(std::string& data);
};
}// namespace model

#endif