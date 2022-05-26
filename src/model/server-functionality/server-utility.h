#ifndef MODEL_SERVER_FUNCTIONALITY_SERVER_UTILITY_H_
#define MODEL_SERVER_FUNCTIONALITY_SERVER_UTILITY_H_

#include <memory>
#include <string>

#include "server-api.h"
#include "server-node.h"

namespace model_server_functionality {
class ServerUtility : public ServerAPI {
 public:
  bool AddServer(const std::string &uuid, const std::string &name, const std::string &owner, const std::string &ip, const std::string &port);
  bool DeleteServer(const std::string &uuid);
  std::shared_ptr<ServerNode> GetServer(const std::string &uuid) const;
};
}  // namespace model_friend_functionality

#endif