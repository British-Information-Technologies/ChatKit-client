#ifndef MODEL_SERVER_FUNCTIONALITY_SERVER_LIST_H_
#define MODEL_SERVER_FUNCTIONALITY_SERVER_LIST_H_

#include <memory>
#include <string>

#include "server-node.h"

namespace model_server_functionality {

class ServerList {
 public:
  virtual bool AddServer(ServerNode &server_node) = 0;
  virtual bool DeleteServer(const std::string &uuid) = 0;
  virtual std::shared_ptr<ServerNode> GetServer(const std::string &uuid) const = 0;
};

}  // namespace model_friend_functionality

#endif