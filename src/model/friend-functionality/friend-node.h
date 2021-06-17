#ifndef CPPCHATCLIENT_MODEL_FRIENDFUNCTIONALITY_FRIENDNODE_
#define CPPCHATCLIENT_MODEL_FRIENDFUNCTIONALITY_FRIENDNODE_

#include <string>

using namespace std;
namespace chat_client_model_friend_functionality {
class FriendNode {
 private:
  string uuid;
  string name;

 public:
  FriendNode(){};
  FriendNode(const string&, const string&);

  string GetUuid();

  string GetName();
};
}  // namespace chat_client_model_friend_functionality

#endif