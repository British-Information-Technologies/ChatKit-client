#ifndef MODEL_SERVER_FUNCTIONALITY_SERVER_HASHMAP_H_
#define MODEL_SERVER_FUNCTIONALITY_SERVER_HASHMAP_H_

#include <map>
#include <memory>
#include <string>

#include "server-list.h"
#include "server-node.h"

namespace model_server_functionality {
class ServerHashmap : public ServerList {
 private:
  std::map<const std::string, std::shared_ptr<ServerNode>> server_map;

 public:
  bool AddServer(ServerNode &server_node);

  bool DeleteServer(const std::string &uuid);

  std::shared_ptr<ServerNode> GetServer(const std::string &uuid) const;
};
}  // namespace model_friend_functionality

#endif