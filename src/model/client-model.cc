#include "client-model.h"

using namespace chat_client_model;
using namespace std;

bool ClientModel::AddFriend(const string& uuid) {
  return friend_api->AddFriend(uuid);
}

shared_ptr<FriendNode> ClientModel::GetFriend(const string& uuid) const {
  return friend_api->GetFriend(uuid);
}
