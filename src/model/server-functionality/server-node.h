#ifndef MODEL_SERVER_FUNCTIONALITY_SERVER_NODE_H_
#define MODEL_SERVER_FUNCTIONALITY_SERVER_NODE_H_

#include <string>

namespace model_server_functionality {
class ServerNode {
 private:
  std::string uuid;
  std::string name;
  std::string owner;

 public:
  ServerNode(const std::string &uuid, const std::string &name, const std::string &owner);

  std::string GetUuid();

  std::string GetName();

  std::string GetOwner();
};
}  // namespace model_friend_functionality

#endif