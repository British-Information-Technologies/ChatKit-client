#ifndef MODEL_SERVER_FUNCTIONALITY_SERVER_LIST_H_
#define MODEL_SERVER_FUNCTIONALITY_SERVER_LIST_H_

#include <map>
#include <memory>
#include <string>

#include "server-node.h"

namespace model_server_functionality {

class ServerList {
public:
    virtual ~ServerList(){};
    virtual std::map<const std::string, std::shared_ptr<ServerNode>>::iterator GetBegin() = 0;
    virtual std::map<const std::string, std::shared_ptr<ServerNode>>::iterator GetEnd() = 0;

    virtual bool AddServer(ServerNode& server_node) = 0;
    virtual bool DeleteServer(const std::string& uuid) = 0;
    virtual std::shared_ptr<ServerNode> GetServer(const std::string& uuid) const = 0;
};

}// namespace model_server_functionality

#endif
