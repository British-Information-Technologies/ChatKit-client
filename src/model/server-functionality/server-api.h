#ifndef MODEL_SERVER_FUNCTIONALITY_SERVER_API_H_
#define MODEL_SERVER_FUNCTIONALITY_SERVER_API_H_

#include <memory>
#include <string>

#include "server-hashmap.h"
#include "server-list.h"

namespace model_server_functionality {
class ServerAPI {
public:
    ServerAPI() { server_list = std::make_unique<ServerHashmap>(); }

    virtual ~ServerAPI() = default;

    virtual std::map<const std::string, std::shared_ptr<ServerNode>>::iterator Begin() = 0;
    virtual std::map<const std::string, std::shared_ptr<ServerNode>>::iterator End() = 0;

    virtual bool AddServer(const std::string& uuid, const std::string& name, const std::string& owner, const std::string& ip, const std::string& port) = 0;
    virtual bool DeleteServer(const std::string& uuid) = 0;
    virtual std::shared_ptr<ServerNode> GetServer(const std::string& uuid) const = 0;

protected:
    std::unique_ptr<ServerList> server_list;
};
} // namespace model_server_functionality

#endif