#ifndef MODEL_FRIEND_FUNCTIONALITY_FRIEND_NODE_H_
#define MODEL_FRIEND_FUNCTIONALITY_FRIEND_NODE_H_

#include <string>

namespace model_friend_functionality {
class FriendNode {
 private:
  std::string uuid;
  std::string name;

 public:
  FriendNode(const std::string&, const std::string&);

  std::string GetUuid();

  std::string GetName();
};
}  // namespace model_friend_functionality

#endif