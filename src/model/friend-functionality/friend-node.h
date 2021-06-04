#ifndef CPPCHATCLIENT_MODEL_FRIENDFUNCTIONALITY_FRIENDNODE_
#define CPPCHATCLIENT_MODEL_FRIENDFUNCTIONALITY_FRIENDNODE_

#include <string>

namespace chat_client_model_friend_functionality {
class FriendNode {
 private:
  std::string uuid;
  std::string name;

 public:
  FriendNode(){};
  FriendNode(std::string *, std::string *);

  std::string GetUuid();

  std::string GetName();
};
}  // namespace chat_client_model_friend_functionality

#endif