#ifndef MODEL_NETWORKING_CONNECTION_TUNNEL_DATA_HANDLER_H_
#define MODEL_NETWORKING_CONNECTION_TUNNEL_DATA_HANDLER_H_

#include <string>

namespace model {
enum class DataHandlerType {
    Insecure = 0,
    Secure = 1,
};

class DataHandler {
public:
    virtual ~DataHandler(){};
    virtual DataHandlerType GetType() = 0;

    virtual std::string FormatSend(std::string& data) = 0;
    virtual std::string FormatRead(std::string& data) = 0;
};
} // namespace model

#endif
